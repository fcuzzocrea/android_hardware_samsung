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

#include <android-base/file.h>
#include <android-base/strings.h>

#include <fstream>

#include "AntiFlickerExynos.h"

using android::base::ReadFileToString;
using android::base::Trim;
using android::base::WriteStringToFile;

namespace vendor {
namespace lineage {
namespace livedisplay {
namespace V2_0 {
namespace samsung {

static constexpr const char* kDcDimmingStatusPath = "/sys/class/lcd/panel/smart_on";

// Methods from ::vendor::lineage::livedisplay::V2_0::IAntiFlicker follow.
bool AntiFlickerExynos::isSupported() {
    std::fstream file(kDcDimmingStatusPath, file.in | file.out);
    return file.good();
}

// Methods from ::vendor::lineage::livedisplay::V2_0::IAntiFlicker follow.
Return<bool> AntiFlickerExynos::isEnabled() {
    std::string tmp;
    int32_t contents = 0;

    if (ReadFileToString(kDcDimmingStatusPath, &tmp)) {
        contents = std::stoi(Trim(tmp));
    }

    return contents > 0;
}

Return<bool> AntiFlickerExynos::showWarning() {
    return true;
}

Return<bool> AntiFlickerExynos::setEnabled(bool enabled) {
    return WriteStringToFile(enabled ? "1" : "0", kDcDimmingStatusPath, true);
}

}  // namespace samsung
}  // namespace V2_0
}  // namespace livedisplay
}  // namespace lineage
}  // namespace vendor
