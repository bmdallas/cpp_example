#include <boost/log/trivial.hpp>
#include <boost/program_options.hpp>
#include <memory>

#include "util/driver.h"

namespace po = boost::program_options;

auto main(int argc, char **argv) -> int {
  // Setup a argument parser to use for this program
  po::options_description program_description("Example driver program options");
  program_description.add_options()("help", "Print help information")(
      "device", po::value<std::string>(),
      "The filepath to the charater device to use");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, program_description), vm);
  po::notify(vm);

  int exit_value = 0;
  if (vm.count("help") || !vm.count("device")) {
    BOOST_LOG_TRIVIAL(info) << program_description;
    exit_value = 1;
  } else {
    // Grab the device passed from the command line
    auto device = vm["device"].as<std::string>();

    // Use a shared_ptr to ensure that it is cleaned up when the
    // program exits.
    auto example_ptr = std::make_shared<util::driver::CharacterDriver>(device);

    // Open the device, and check that it worked
    if (example_ptr->open()) {
      BOOST_LOG_TRIVIAL(info)
          << "Opened device with name " << example_ptr->getName();

      // Write "Hello Drivers!" to the opened device
      const std::string example_message = "Hello Drivers!";
      BOOST_LOG_TRIVIAL(info) << "Writing \"" << example_message << "\" to "
                              << example_ptr->getName();
      if (!example_ptr->write(std::span(example_message))) {
        // The write failed. Notify the user and exit
        BOOST_LOG_TRIVIAL(error) << "Could not write to " << device;
        exit(-1);
      }

      // Read data back from the character driver
      constexpr std::size_t BUFFER_SIZE = 1024;
      std::array<char, BUFFER_SIZE> array{};
      std::span<char> char_span{array};
      if (example_ptr->read(char_span)) {
        // Notify the user the data that was read
        BOOST_LOG_TRIVIAL(info) << "Read: " << std::string{char_span.data()};
      } else {
        // Notify the user that the read failed
        BOOST_LOG_TRIVIAL(error) << "Could not read from " << device;
        // TODO(bmdallas) wouldn't it be nice if this was standardized...
        exit_value = -1;
      }
    } else {
      // Notify the user of the failed attempt to open the device
      BOOST_LOG_TRIVIAL(fatal) << "Could not open " << device;
      exit_value = -1;
    }
  }

  return exit_value;
}
