/*
makenar - Low quality tool for creating nar files.
This file is placed in the public domain, or under the licence of the main distribution otherwise.

This utility will very likely be replaced in the future with a more robust and complete one.

Usage: makenar [archive] [files]
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {

  if (argc < 2) {
    fprintf(stderr, "Usage: %s [archive] [files]\n", argv[0]);
    exit(1);
  }

  FILE* archive = fopen(argv[1], "wb");

  fwrite("NAR\x01", 1, 4, archive);
  uint32_t num_files = argc - 2;
  fwrite(&num_files, 1, 4, archive);

  for (int i = 2; i < argc; i++) {
    uint32_t name_length = strlen(argv[i]);
    fwrite(&name_length, 1, 4, archive);

    FILE* file = fopen(argv[i], "rb");
    fseek(file, 0, SEEK_END);
    uint64_t size = ftell(file);
    rewind(file);

    fwrite(&size, 1, 8, archive);

    uint64_t metadata = 0;
    fwrite(&metadata, 1, 8, archive);

    fwrite(argv[i], 1, strlen(argv[i]), archive);

    uint8_t* contents = malloc(size);
    fread(contents, 1, size, file);

    fwrite(contents, 1, size, archive);

    fclose(file);
  }

  return 0;
  
}