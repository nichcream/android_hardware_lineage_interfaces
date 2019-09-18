/*
 * Copyright (C) 2019 The LineageOS Project
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

#pragma once

#include <vendor/qti/hardware/cryptfshw/1.0/ICryptfsHw.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>

namespace vendor {
namespace qti {
namespace hardware {
namespace cryptfshw {
namespace V1_0 {
namespace implementation {

using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;

enum cryptfs_hw_key_management_usage_type {
    CRYPTFS_HW_KM_USAGE_DISK_ENCRYPTION			= 0x01,
    CRYPTFS_HW_KM_USAGE_FILE_ENCRYPTION			= 0x02,
    CRYPTFS_HW_KM_USAGE_UFS_ICE_DISK_ENCRYPTION		= 0x03,
    CRYPTFS_HW_KM_USAGE_SDCC_ICE_DISK_ENCRYPTION	= 0x04,
    CRYPTFS_HW_KM_USAGE_MAX
};

struct CryptfsHw : public ICryptfsHw {
public:
    // Methods from ::vendor::qti::hardware::cryptfshw::V1_0::ICryptfsHw follow.
    Return<int32_t> setIceParam(uint32_t flag) override;
    Return<int32_t> setKey(const hidl_string& passwd, const hidl_string& enc_mode) override;
    Return<int32_t> updateKey(const hidl_string& oldpw, const hidl_string& newpw,
            const hidl_string& enc_mode) override;
    Return<int32_t> clearKey() override;

private:
    int cryptfs_hw_create_key(enum cryptfs_hw_key_management_usage_type usage,
            unsigned char *hash32);
    int __cryptfs_hw_wipe_clear_key(enum cryptfs_hw_key_management_usage_type usage,
            int wipe_key_flag);
    int cryptfs_hw_wipe_key(enum cryptfs_hw_key_management_usage_type usage);
    int cryptfs_hw_clear_key(enum cryptfs_hw_key_management_usage_type usage);
    int cryptfs_hw_update_key(enum cryptfs_hw_key_management_usage_type usage,
            unsigned char *current_hash32, unsigned char *new_hash32);
    enum cryptfs_hw_key_management_usage_type map_usage(
            enum cryptfs_hw_key_management_usage_type usage);
    unsigned char* get_tmp_passwd(const char* passwd);
    int is_qseecom_up();
    int set_key(const char* currentpasswd, const char* passwd, const char* enc_mode, int operation);
};

}  // namespace implementation
}  // namespace V1_0
}  // namespace cryptfshw
}  // namespace hardware
}  // namespace qti
}  // namespace vendor
