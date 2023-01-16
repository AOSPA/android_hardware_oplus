#
# Copyright (C) 2022 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#
BOARD_VENDOR_SEPOLICY_DIRS += hardware/oplus/sepolicy/qti/vendor
SYSTEM_EXT_PRIVATE_SEPOLICY_DIRS += hardware/oplus/sepolicy/qti/private
SYSTEM_EXT_PUBLIC_SEPOLICY_DIRS += hardware/oplus/sepolicy/qti/public

ifneq ($(call is-board-platform-in-list,$(5_4_FAMILY) $(5_10_FAMILY)),true)
BOARD_VENDOR_SEPOLICY_DIRS += hardware/oplus/sepolicy/legacy/vendor
endif
