#
# Copyright (C) 2024 Paranoid Android
#
# SPDX-License-Identifier: Apache-2.0
#

ifeq ($(call is-board-platform-in-list,$(4_14_FAMILY) $(4_19_FAMILY)),true)
    SEPOLICY_PLATFORM := legacy-um
else
    SEPOLICY_PLATFORM := um
endif

BOARD_VENDOR_SEPOLICY_DIRS += \
    hardware/oplus/sepolicy/qti/vendor \
    hardware/oplus/sepolicy/qti/vendor/$(SEPOLICY_PLATFORM)

SYSTEM_EXT_PRIVATE_SEPOLICY_DIRS += \
    hardware/oplus/sepolicy/qti/private \
    hardware/oplus/sepolicy/qti/private/$(SEPOLICY_PLATFORM)

SYSTEM_EXT_PUBLIC_SEPOLICY_DIRS += \
    hardware/oplus/sepolicy/qti/public \
    hardware/oplus/sepolicy/qti/public/$(SEPOLICY_PLATFORM)
