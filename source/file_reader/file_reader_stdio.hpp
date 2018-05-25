#ifndef NH_FILE_READER_STDIO_H
#define NH_FILE_READER_STDIO_H

#include <cstdio>
#include <cstring>

#include <cerrno>

#include "file_reader_base.hpp"

namespace nh {

class file_reader_stdio_t : public file_reader_base_t {

  public:

  file_reader_stdio_t(std::string file);

  size_t read_bytes(size_t num_bytes, uint8_t* destination);
  void set_pos_absolute(size_t pos);
  void set_pos_forwards(size_t pos);
  void set_pos_backwards(size_t pos);
  size_t get_pos();
  size_t get_length();

  private:
  FILE* file;

};

}

#endif
