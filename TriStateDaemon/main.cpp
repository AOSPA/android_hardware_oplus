/*
 * Copyright (C) 2020 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "tri-state-key_daemon"

#include <android-base/file.h>
#include <android-base/logging.h>
#include <fcntl.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <unistd.h>

#include "uevent_listener.h"

#define TRI_STATE_KEY_STATE "/proc/tristatekey/tri_state"
#define HALL_CALIBRATION_DATA "/proc/tristatekey/hall_data_calib"
#define HALL_PERSIST_CALIBRATION_DATA "/mnt/vendor/persist/engineermode/tri_state_hall_data"

#define KEY_MODE_NORMAL 601
#define KEY_MODE_VIBRATION 602
#define KEY_MODE_SILENCE 603

using android::base::ReadFileToString;
using android::base::WriteStringToFile;
using android::Uevent;
using android::UeventListener;

template <typename T>
static T get(const std::string& path, const T& def) {
    std::ifstream file(path);
    T result;

    file >> result;
    return file.fail() ? def : result;
}

int main() {
    int err;
    int uinputFd;
    struct uinput_user_dev uidev {};
    UeventListener uevent_listener;

    LOG(INFO) << "Started";

    if (std::string hallData; ReadFileToString(HALL_PERSIST_CALIBRATION_DATA, &hallData)) {
        std::replace(hallData.begin(), hallData.end(), ';', ',');
        WriteStringToFile(hallData, HALL_CALIBRATION_DATA);
    }

    uinputFd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (uinputFd < 0) {
        LOG(ERROR) << "Unable to open uinput node";
        return 1;
    }

    err = ioctl(uinputFd, UI_SET_EVBIT, EV_KEY) |
          ioctl(uinputFd, UI_SET_KEYBIT, KEY_MODE_NORMAL) |
          ioctl(uinputFd, UI_SET_KEYBIT, KEY_MODE_VIBRATION) |
          ioctl(uinputFd, UI_SET_KEYBIT, KEY_MODE_SILENCE);
    if (err != 0) {
        LOG(ERROR) << "Unable to enable KEY events";
        goto out;
    }

    sprintf(uidev.name, "uinput-tri-state-key");
    uidev.id.bustype = BUS_VIRTUAL;

    err = write(uinputFd, &uidev, sizeof(uidev));
    if (err < 0) {
        LOG(ERROR) << "Write user device to uinput node failed";
        goto out;
    }

    err = ioctl(uinputFd, UI_DEV_CREATE);
    if (err < 0) {
        LOG(ERROR) << "Unable to create uinput device";
        goto out;
    }

    LOG(INFO) << "Successfully registered uinput-tri-state-key for KEY events";

    uevent_listener.Poll([&uinputFd](const Uevent& uevent) {
        int err;
        int keyCode;
        string keyState;
        struct input_event event {};

        if (uevent.action != "change" || uevent.name != "oplus,hall_tri_state_key") {
            return;
        }

		keyState = get(TRI_STATE_KEY_STATE);

        if (keyState == "1") {
            keyCode = KEY_MODE_NORMAL;
        } else if (keyState == "2") {
            keyCode = KEY_MODE_VIBRATION;
        } else if (keyState == "3") {
            keyCode = KEY_MODE_SILENCE;
        } else {
            // Ignore intermediate states
            return;
        }

        // Report the key
        event.type = EV_KEY;
        event.code = keyCode;
        event.value = 1;
        err = write(uinputFd, &event, sizeof(event));
        if (err < 0) {
            LOG(ERROR) << "Write EV_KEY to uinput node failed";
            return;
        }

        // Force a flush with an EV_SYN
        event.type = EV_SYN;
        event.code = SYN_REPORT;
        event.value = 0;
        err = write(uinputFd, &event, sizeof(event));
        if (err < 0) {
            LOG(ERROR) << "Write EV_SYN to uinput node failed";
            return;
        }

        // Report the key
        event.type = EV_KEY;
        event.code = keyCode;
        event.value = 0;
        err = write(uinputFd, &event, sizeof(event));
        if (err < 0) {
            LOG(ERROR) << "Write EV_KEY to uinput node failed";
            return;
        }

        // Force a flush with an EV_SYN
        event.type = EV_SYN;
        event.code = SYN_REPORT;
        event.value = 0;
        err = write(uinputFd, &event, sizeof(event));
        if (err < 0) {
            LOG(ERROR) << "Write EV_SYN to uinput node failed";
            return;
        }

        return;
    });

out:
    // Clean up
    close(uinputFd);

    // The loop can only be exited via failure or signal
    return 1;
}
