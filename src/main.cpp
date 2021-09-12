#include <boost/log/trivial.hpp>
#include <boost/program_options.hpp>
#include <memory>

#include "util/driver.h"

namespace po = boost::program_options;

auto main(int argc, char **argv) -> int {
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
    auto device = vm["device"].as<std::string>();

    // Use a shared_ptr to ensure that it is cleaned up when the
    // program exits.
    auto example_ptr = std::make_shared<util::driver::CharacterDriver>(device);

    if (example_ptr->open()) {
      const std::string example_message = "Hello Drivers!";
      BOOST_LOG_TRIVIAL(info) << "Opened device with name " << example_ptr->getName();

      BOOST_LOG_TRIVIAL(info) << "Writing \"" << example_message << "\" to " << example_ptr->getName();
      if (!example_ptr->write(std::span(example_message))) {
        BOOST_LOG_TRIVIAL(error) << "Could not write to " << device;
        exit(-1);
      }

      constexpr std::size_t BUFFER_SIZE = 1024;
      std::array<char, BUFFER_SIZE> array{};
      std::span<char> char_span{array};
      if (example_ptr->read(char_span)) {
        BOOST_LOG_TRIVIAL(info) << "Read: " << std::string{char_span.data()};
      } else {
        BOOST_LOG_TRIVIAL(error) << "Could not read from " << device;
      }
    } else {
      BOOST_LOG_TRIVIAL(fatal) << "Could not open " << device;
    }
  }

  return exit_value;
}
