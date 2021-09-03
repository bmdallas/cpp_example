#ifndef PUBLIC_UTIL_DRIVER_H
#define PUBLIC_UTIL_DRIVER_H

// This include is minimum C++17 compatible
#include <filesystem>

// This format requires C++17
namespace util::driver {

/**
 * Currently this class has no functionality, but is used as example
 * code.
 */
class ADriver {
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

  /**
   * Default copy constructor
   */
  ADriver(const ADriver & /*other*/) = default;

  /**
   * Default move constructor
   */
  ADriver(ADriver && /*other*/) = default;

  /**
   * Default copy assignment operator
   */
  auto operator=(const ADriver & /*other*/) -> ADriver & = default;

  /**
   * Default move assignment operator
   */
  auto operator=(ADriver && /*other*/) -> ADriver & = default;

 private:
};

class ACharacterDriver : public ADriver {
 public:
  /**
   * The default constructor takes a filesystem path that points to the
   * linux character device which the driver will use.
   */
  explicit ACharacterDriver(std::filesystem::path /*path*/);

  /**
   * This is the destructor, uses the C++11 compatible override keyword
   * instead of virtual.
   */
  ~ACharacterDriver() override = default;

  /**
   * Default copy constructor
   */
  ACharacterDriver(const ACharacterDriver & /*other*/) = default;

  /**
   * Default move constructor
   */
  ACharacterDriver(ACharacterDriver && /*other*/) = default;

  /**
   * Default copy assignment operator
   */
  auto operator=(const ACharacterDriver & /*other*/)
      -> ACharacterDriver & = default;

  /**
   * Default move assignment operator
   */
  auto operator=(ACharacterDriver && /*other*/) -> ACharacterDriver & = default;

 private:
  //! This holds the filesystem path to the device (e.g. /dev/tty0)
  std::filesystem::path _device_path;
};

}  // namespace util::driver

#endif  // PUBLIC_UTIL_DRIVER_H
