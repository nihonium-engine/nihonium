#ifndef NH_FILE_READER_BASE_H
#define NH_FILE_READER_BASE_H

#include <cstddef>
#include <cstdint>

#include <string>

namespace nh {

class BaseFileReader {

  public:

  bool eof;

  virtual size_t read_bytes(size_t num_bytes, uint8_t* destination) = 0;
  virtual void set_pos_absolute(size_t pos) = 0;
  virtual void set_pos_forwards(size_t pos) = 0;
  virtual void set_pos_backwards(size_t pos) = 0;
  uint8_t read_uint8();
  uint32_t read_uint32();
  uint64_t read_uint64();

  virtual size_t get_pos() = 0;

};

}

#endif
