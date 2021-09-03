#include "util/driver.h"

namespace util::driver {

ACharacterDriver::ACharacterDriver(const std::filesystem::path &path)
    : _device_path(path) {}

}  // namespace util::driver
