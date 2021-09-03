#include <memory>

#include "example.h"

int main(int argc, char **argv) {
  // Use a shared_ptr to ensure that it is cleaned up when the
  // program exits.
  auto example_ptr = std::make_shared<example::Example>();
  return 0;
}
