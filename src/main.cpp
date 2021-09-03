#include <memory>

#include "util/driver.h"

int main(int argc, char **argv) {
  // Use a shared_ptr to ensure that it is cleaned up when the
  // program exits.
  auto example_ptr =
      std::make_shared<util::driver::ACharacterDriver>("/dev/tty0");
  return 0;
}
