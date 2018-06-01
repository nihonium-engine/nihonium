#ifndef NH_MOUNT_DIRECTORY_H
#define NH_MOUNT_DIRECTORY_H

#include "mount_base.hpp"

namespace nh {

class file_directory_t : public file_base_t {

  public:
  file_directory_t(FILE* file);
  ~file_directory_t();

  void seek_current(int offset) override;
  void seek_start(int offset) override;
  void seek_end(int offset) override;

  size_t tell() override;

  size_t read(size_t bytes, uint8_t* dest) override;

  void close() override;
  bool eof() override;

  private:
  FILE* file;

};

class mount_directory_t {

  public:
  mount_directory_t(std::string base_path);
  ~mount_directory_t();

  file_base_t* open_file(std::string path);

  private:
  std::string base_path;

};

}

#endif
