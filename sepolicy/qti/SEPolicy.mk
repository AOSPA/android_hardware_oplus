#
# Copyright (C) 2024 Paranoid Android
#
# SPDX-License-Identifier: Apache-2.0
#

ifeq ($(call is-board-platform-in-list,$(4_14_FAMILY) lito kona),true)
    SEPOLICY_PLATFORM := legacy-um
else ifeq ($(call is-board-platform,bengal),true)
    SEPOLICY_PLATFORM := legacy-um-bengal
else ifeq ($(call is-board-platform,holi),true)
    SEPOLICY_PLATFORM := legacy-um-holi
else ifeq ($(call is-board-platform,lahaina),true)
    SEPOLICY_PLATFORM := legacy-um-lahaina
else ifeq ($(call is-board-platform-in-list,$(5_10_FAMILY)),true)
    SEPOLICY_PLATFORM := sm8450
else ifeq ($(call is-board-platform-in-list,$(5_15_FAMILY)),true)
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

ifneq ($(SEPOLICY_PLATFORM), legacy-um legacy-um-bengal legacy-um-holi legacy-um-lahaina)
BOARD_VENDOR_SEPOLICY_DIRS += \
    hardware/oplus/sepolicy/qti/vendor/common-um

SYSTEM_EXT_PRIVATE_SEPOLICY_DIRS += \
    hardware/oplus/sepolicy/qti/private/common-um

SYSTEM_EXT_PUBLIC_SEPOLICY_DIRS += \
    hardware/oplus/sepolicy/qti/public/common-um
else ifeq ($(SEPOLICY_PLATFORM), legacy-um legacy-um-bengal legacy-um-holi legacy-um-lahaina)
BOARD_VENDOR_SEPOLICY_DIRS += \
    hardware/oplus/sepolicy/qti/vendor/common-legacy-um

SYSTEM_EXT_PRIVATE_SEPOLICY_DIRS += \
    hardware/oplus/sepolicy/qti/private/common-legacy-um

SYSTEM_EXT_PUBLIC_SEPOLICY_DIRS += \
    hardware/oplus/sepolicy/qti/public/common-legacy-um
endif
