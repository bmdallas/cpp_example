#include "util/driver.h"

namespace util::driver {

ACharacterDriver::ACharacterDriver(std::filesystem::path path)
    : _device_path(std::move(path)) {}

}  // namespace util::driver
