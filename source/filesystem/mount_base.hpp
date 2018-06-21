#ifndef NH_MOUNT_BASE_H
#define NH_MOUNT_BASE_H

#include <cstdint>
#include <map>

namespace nh {

class file_base_t {

  public:
  virtual ~file_base_t() {};

  virtual void seek_current(int offset) = 0;
  virtual void seek_start(int offset) = 0;
  virtual void seek_end(int offset) = 0;

  virtual size_t tell() = 0;

  virtual size_t read(size_t bytes, uint8_t* dest) = 0;

  virtual void close() = 0;
  virtual bool eof() = 0;

  uint16_t read_uint16();
  uint32_t read_uint32();
  uint64_t read_uint64();

};

class mount_base_t {

  public:
  virtual file_base_t* open_file(std::string path) = 0;

};

}

#endif
