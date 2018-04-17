#include "file_reader_stdio.hpp"

namespace nh {

StdioFileReader::StdioFileReader(std::string file) {

  this->file = fopen(file.c_str(), "rb");

}

size_t StdioFileReader::read_bytes(size_t num_bytes, uint8_t* destination) {

  size_t bytes_read = fread(destination, 1, num_bytes, this->file);

  this->eof = feof(this->file) != 0;

  return bytes_read;

}

void StdioFileReader::set_pos_absolute(size_t pos) {
  fseek(this->file, pos, SEEK_SET);
}

void StdioFileReader::set_pos_forwards(size_t pos) {
  fseek(this->file, pos, SEEK_CUR);
}

void StdioFileReader::set_pos_backwards(size_t pos) {
  fseek(this->file, -pos, SEEK_CUR);
}

size_t StdioFileReader::get_pos() {

  return ftell(this->file);

}

}