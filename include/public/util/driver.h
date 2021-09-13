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

  /**
   * This method will return the name of the device
   *
   * @return A string with the name of the device.
   */
  virtual auto getName() -> const std::string&;

  /**
   * This is a pure virtual method to be implemented by derived classes
   * to open the device correctly for their implementation.
   *
   * @return True on success, False otherwise
   */
  virtual auto open() -> bool = 0;

 private:
  std::string _name;
};

/**
 * This is a Driver that controls Linux Character device drivers
 * (e.g. /dev/ttyUSB0). It currently implements read and write,
 * but could be expanded to support mmap, and ioctl calls in the
 * future. New classes can inherit from this class and add specialized
 * functions for their specific device.
 *
 * This inherits from ADrivers to support polymorphism in as this library
 * expands.
 */
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
   *
   * @return True if opened, False otherwise
   */
  auto open() -> bool override;

  /**
   * This method will read from the device based on the size of the span
   * provided
   *
   * @tparam T Any type, it will automatically be converted from bytes
   * @param read_data A std::span that holds the data structures that will be
   * read in from the device
   * @return True if the read succeeds, False otherwise.
   *
   * TODO(bmdallas) find a way to handle error codes
   */
  template <typename T>
  auto read(std::span<T> read_data) -> bool {
    // NOLINTNEXTLINE
    _fd.read(reinterpret_cast<char*>(std::as_writable_bytes(read_data).data()),
             read_data.size_bytes());

    return (_fd ? true : false);
  }

  /**
   * This method will write to the device based on span provided
   *
   * @tparam T Any type, it will automatically be converted to bytes
   * @param read_data A std::span that holds the data structures that will be
   * written to the device
   * @return True if the write succeeds, False otherwise.
   *
   * TODO(bmdallas) find a way to handle error codes
   */
  template <typename T>
  auto write(std::span<T> write_data) -> bool {
    // NOLINTNEXTLINE
    _fd.write(reinterpret_cast<const char*>(std::as_bytes(write_data).data()),
              write_data.size_bytes());

    return (_fd ? true : false);
  }

 private:
  //! This holds the filesystem path to the device (e.g. /dev/tty0)
  std::filesystem::path _device_path;

  //! This holds the fstream that is opened for the character device
  std::fstream _fd;
};

}  // namespace util::driver

#endif  // PUBLIC_UTIL_DRIVER_H
