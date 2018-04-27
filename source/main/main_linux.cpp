
#include "../screen/glfw.hpp"

#include "../file_reader/file_reader_stdio.hpp"
#include "../file_reader/file_reader_nar.hpp"

#include <stdio.h>

int main(int argc, char** argv) {

  (void)argc; (void)argv;

  nh::file_reader_stdio_t* file_reader = new nh::file_reader_stdio_t("test.nar");
  nh::file_reader_nar_t* nar_reader = new nh::file_reader_nar_t("LICENCE.txt", file_reader);

  char* bytes = new char[21];
  nar_reader->read_bytes(20, (uint8_t*)bytes);
  bytes[21] = '\0';

  printf("%s\n", bytes);

  return 0;

}