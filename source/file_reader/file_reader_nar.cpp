#include "file_reader_nar.hpp"

namespace nh {

file_reader_nar_t::file_reader_nar_t(std::string file, file_reader_base_t* source_reader) {

  this->source_reader = source_reader;

  uint32_t header = this->source_reader->read_uint32();
  uint8_t* header_bytes = (uint8_t*)&header;

  if (memcmp(header_bytes, "NAR", 3) != 0) {
    throw std::exception();
  }

  if (header_bytes[3] != 0x01) {
    throw std::exception();
  }

  uint32_t num_files = this->source_reader->read_uint32();

  for (uint32_t i = 0; i < num_files; i++) {

    uint32_t file_name_length = this->source_reader->read_uint32();
    uint64_t file_contents_length = this->source_reader->read_uint64();

    uint8_t file_metadata[8];
    this->source_reader->read_bytes(8, file_metadata);

    char* file_name = new char[file_name_length];
    this->source_reader->read_bytes(file_name_length, (uint8_t*)file_name);

    // We check if the lengths are identical first as that will immediately invalidate most non-matching file names.
    // It also makes the string comparison somewhat easier to do safely.
    if (file_name_length == file.length()) {

      if (memcmp(file_name, file.c_str(), file_name_length) == 0) {

        this->file_start_offset = source_reader->get_pos();
        this->offset_in_file = 0;
        this->compression_format = file_metadata[0];
        this->file_length = file_contents_length;

        return;

      }
    }
  }

  throw file_not_found_exception_t();

}

size_t file_reader_nar_t::read_bytes(size_t num_bytes, uint8_t* destination) {

  this->source_reader->set_pos_absolute(this->file_start_offset + this->offset_in_file);
  size_t bytes_read = this->source_reader->read_bytes(num_bytes, destination);

  this->eof = this->source_reader->eof;

  return bytes_read;
}

void file_reader_nar_t::set_pos_absolute(size_t pos) {
  this->offset_in_file = pos > this->file_length ? this->file_length : pos;
}

void file_reader_nar_t::set_pos_forwards(size_t pos) {
  this->offset_in_file = (this->offset_in_file + pos) > this->file_length ? this->file_length : this->offset_in_file + pos;
}

void file_reader_nar_t::set_pos_backwards(size_t pos) {
  this->offset_in_file = pos > this->offset_in_file ? 0 : this->offset_in_file - pos;
}


size_t file_reader_nar_t::get_pos() {
  return this->offset_in_file;
}

}
