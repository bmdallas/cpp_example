#ifndef PUBLIC_UTIL_DRIVER_H
#define PUBLIC_UTIL_DRIVER_H

// This include is minimum C++17 compatible
#include <filesystem>
#include <fstream>
#include <span>

// This format requires C++17
namespace util::driver {

/**
 * This class is an abstract driver class that all Linux drivers
 * will inherit from. This will make it easier to hold disperate
 * drivers in a common structure if necessary.
 */
class ADriver {
 public:
  /**
   * Create the default constructor and make it explicit so that
   * it does not get automatically created based on the compilers
   * interpretation of casting code.
   */
  explicit ADriver(std::string /*name*/);

  /**
   * Create the default constructor, ensure that it is virtual.
   */
  virtual ~ADriver() = default;

  /**
   * Default copy constructor
   */
  ADriver(const ADriver& /*other*/) = default;

  /**
   * Default move constructor
   */
  ADriver(ADriver&& /*other*/) = default;

  /**
   * Default copy assignment operator
   */
  auto operator=(const ADriver & /*other*/) -> ADriver& = default;

  /**
   * Default move assignment operator
   */
  auto operator=(ADriver && /*other*/) -> ADriver& = default;

  virtual auto getName() -> const std::string&;

  virtual auto open() -> bool = 0;

 private:
  std::string _name;
};

class CharacterDriver : public ADriver {
 public:
  /**
   * The default constructor takes a filesystem path that points to the
   * linux character device which the driver will use.
   */
  explicit CharacterDriver(std::filesystem::path /*path*/);

  /**
   * This is the destructor, uses the C++11 compatible override keyword
   * instead of virtual.
   */
  ~CharacterDriver() override = default;

  /**
   * Default copy constructor
   *
   * This is deleted due to the use of fstream
   */
  CharacterDriver(const CharacterDriver& /*other*/) = delete;

  /**
   * Default move constructor
   */
  CharacterDriver(CharacterDriver&& /*other*/) = default;

  /**
   * Default copy assignment operator.
   *
   * This is deleted due to the use of fstream
   */
  auto operator=(const CharacterDriver & /*other*/)
      -> CharacterDriver& = delete;

  /**
   * Default move assignment operator
   */
  auto operator=(CharacterDriver && /*other*/) -> CharacterDriver& = default;

  /**
   * This method will open the device provided in the constructor,
   * and will return the status of opening the device.
   */
  auto open() -> bool override;

  /**
   * This method will read from the device.
   */
  template <typename T>
  auto read(std::span<T> read_data) -> bool {
    return _fd.read(std::as_writable_bytes(read_data), read_data.size_bytes());
  }

 private:
  //! This holds the filesystem path to the device (e.g. /dev/tty0)
  std::filesystem::path _device_path;
  std::fstream _fd;
};

}  // namespace util::driver

#endif  // PUBLIC_UTIL_DRIVER_H
