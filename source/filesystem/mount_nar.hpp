#ifndef NH_MOUNT_NAR_H
#define NH_MOUNT_NAR_H

#include <cstdint>
#include <cstdio>
#include <cstring>

#include "mount_base.hpp"

namespace nh {

class file_nar_t : public file_base_t {

  public:
  file_nar_t(uint64_t file_start_offset, uint64_t file_size, FILE* base_file);
  
  void seek_current(int offset) override;
  void seek_start(int offset) override;
  void seek_end(int offset) override;

  size_t read(size_t bytes, uint8_t* dest) override;

  void close() override;
  bool eof() override;

  private:
  uint64_t file_start_offset;
  uint64_t file_size;
  uint64_t current_offset;
  FILE* base_file;

};

class mount_nar_t : public mount_base_t {

  struct file_data_t {
    uint64_t offset;
    uint64_t size;
  };

  public:
  mount_nar_t(std::string nar_path);
  ~mount_nar_t();
  
  file_base_t* open_file(std::string path);

  private:
  std::map<std::string, file_data_t> file_cache;
  FILE* base_file;

};

}

#endif
