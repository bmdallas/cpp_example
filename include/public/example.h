// Most modern compilers support this now.
#pragma once

// This include is minimum C++17 compatible
#include <filesystem>

namespace linux
{

/**
 * Currently this class has no functionality, but is used as example
 * code.
 */
class ADriver
{
public:
    /** 
     * Create the default constructor and make it explicit so that
     * it does not get automatically created based on the compilers
     * interpretation of casting code.
     */
    explicit ADriver() = default;

    /**
     * Create the default constructor, ensure that it is virtual.
     */
    virtual ~ADriver() = default;

private:
};

class ACharacterDriver : public ADriver
{
public:
    /**
     * The default constructor takes a filesystem path that points to the
     * linux character device which the driver will use.
     */
    explicit ACharacterDriver(const std::filesystem::path&);
    
    /**
     * This is the destructor, uses the C++11 compatible override keyword
     * instead of virtual.
     */
    ~ACharacterDriver() override = default;

private:
    //! This holds the filesystem path to the device (e.g. /dev/tty0)
    std::filesystem::path _device_path;
};

} // namespace example
