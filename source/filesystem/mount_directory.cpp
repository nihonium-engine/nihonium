#include "mount_directory.hpp"

namespace nh {

file_directory_t::file_directory_t(FILE* file) {
  this->file = file;
}

file_directory_t::~file_directory_t() {
  if (this->file) {
    fclose(this->file);
  }
}

void file_directory_t::seek_current(int offset) {
  fseek(this->file, offset, SEEK_CUR);
}

void file_directory_t::seek_start(int offset) {
  fseek(this->file, offset, SEEK_SET);
}

void file_directory_t::seek_end(int offset) {
  fseek(this->file, -offset, SEEK_END);
}

size_t file_directory_t::tell() {

  return ftell(this->file);

}

size_t file_directory_t::read(size_t bytes, uint8_t* dest) {
  return fread(dest, 1, bytes, this->file);
}

void file_directory_t::close() {
  fclose(this->file);
  this->file = nullptr;
}

bool file_directory_t::eof() {
  return feof(this->file);
}

mount_directory_t::mount_directory_t(std::string base_path) {
  this->base_path = base_path;
}

mount_directory_t::~mount_directory_t() {
  
}

file_base_t* mount_directory_t::open_file(std::string path) {
  FILE* stdio_file = fopen((this->base_path + path).c_str(), "rb");
  file_directory_t* file = new file_directory_t(stdio_file);
  return file;
}

}
