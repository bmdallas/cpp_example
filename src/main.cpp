#include <memory>

#include "util/driver.h"

auto main(int argc, char **argv) -> int {
  // Use a shared_ptr to ensure that it is cleaned up when the
  // program exits.
  auto example_ptr =
      std::make_shared<util::driver::CharacterDriver>("/dev/tty0");
  return 0;
}
