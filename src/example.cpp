#include "example.h"

namespace linux
{

ACharacterDriver::ACharacterDriver(const std::filesystem::path& path) :
    _device_path(path)
{

    
}

} // namespace linux
