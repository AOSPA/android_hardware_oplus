#
# Copyright (C) 2024 Paranoid Android
#
# SPDX-License-Identifier: Apache-2.0
#

ifeq ($(call is-board-platform-in-list,$(4_14_FAMILY) $(4_19_FAMILY)),true)
    SEPOLICY_PLATFORM := legacy-um
else ifeq ($(SEPOLICY_PATH), device/qcom/sepolicy_vndr/sm8450)
    SEPOLICY_PLATFORM := sm8450
else ifeq ($(SEPOLICY_PATH), device/qcom/sepolicy_vndr/sm8550)
    SEPOLICY_PLATFORM := sm8550
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

ifneq ($(SEPOLICY_PLATFORM), legacy-um)
BOARD_VENDOR_SEPOLICY_DIRS += \
    hardware/oplus/sepolicy/qti/vendor/common-um

SYSTEM_EXT_PRIVATE_SEPOLICY_DIRS += \
    hardware/oplus/sepolicy/qti/private/common-um

SYSTEM_EXT_PUBLIC_SEPOLICY_DIRS += \
    hardware/oplus/sepolicy/qti/public/common-um
endif
