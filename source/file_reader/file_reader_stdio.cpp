#include "file_reader_stdio.hpp"

namespace nh {

file_reader_stdio_t::file_reader_stdio_t(std::string file) {

  this->file = fopen(file.c_str(), "rb");

  if (!this->file) {
    if (errno == ENOENT) {
      throw file_not_found_exception_t();
    }
  }

}

size_t file_reader_stdio_t::read_bytes(size_t num_bytes, uint8_t* destination) {

  size_t bytes_read = fread(destination, 1, num_bytes, this->file);

  this->eof = feof(this->file) != 0;

  return bytes_read;

}

void file_reader_stdio_t::set_pos_absolute(size_t pos) {
  fseek(this->file, pos, SEEK_SET);
}

void file_reader_stdio_t::set_pos_forwards(size_t pos) {
  fseek(this->file, pos, SEEK_CUR);
}

void file_reader_stdio_t::set_pos_backwards(size_t pos) {
  fseek(this->file, -pos, SEEK_CUR);
}

size_t file_reader_stdio_t::get_pos() {

  return ftell(this->file);

}

size_t file_reader_stdio_t::get_length() {
  size_t current_pos = ftell(this->file);
  fseek(this->file, 0, SEEK_END);
  size_t length = ftell(this->file);
  fseek(this->file, current_pos, SEEK_SET);
  return length;
}

}