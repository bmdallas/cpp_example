#include "util/driver.h"

namespace util::driver {

ADriver::ADriver(std::string name) : _name(std::move(name)) {}

auto ADriver::getName() -> const std::string& { return _name; }

CharacterDriver::CharacterDriver(std::filesystem::path path)
    : ADriver(path.string()), _device_path(std::move(path)) {}

auto CharacterDriver::open() -> bool {
  // TODO(bmdallas) This function currently only supports reading from the file.
  _fd.open(_device_path.string(), std::ios::in | std::ios::out);
  return _fd.is_open();
}

}  // namespace util::driver
