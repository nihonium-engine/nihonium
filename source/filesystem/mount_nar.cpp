#include "mount_nar.hpp"

namespace nh {

file_nar_t::file_nar_t(uint64_t file_start_offset, uint64_t file_size, FILE* base_file) {
  this->file_start_offset = file_start_offset;
  this->file_size = file_size;
  this->base_file = base_file;
  this->current_offset = 0;
}

void file_nar_t::seek_current(int offset) {
  this->current_offset += offset;
}

void file_nar_t::seek_start(int offset) {
  this->current_offset = offset;
}

void file_nar_t::seek_end(int offset) {
  this->current_offset = this->file_size - offset;
}

size_t file_nar_t::tell() {
  return this->current_offset;
}

size_t file_nar_t::read(size_t bytes, uint8_t* dest) {
  this->eof_marker = false;

  if (this->current_offset + bytes > this->file_size) {
    bytes = this->file_size - this->current_offset;
    this->eof_marker = true;
  }

  fseek(this->base_file, this->file_start_offset + this->current_offset, SEEK_SET);
  size_t bytes_read = fread(dest, 1, bytes, this->base_file);
  this->current_offset += bytes_read;
  return bytes_read;
}

void file_nar_t::close() {
  this->base_file = nullptr;
}

bool file_nar_t::eof() {
  return eof_marker;
}

mount_nar_t::mount_nar_t(std::string nar_path) {
  this->base_file = fopen(nar_path.c_str(), "rb");

  uint8_t header[4];

  fread(header, 1, 4, this->base_file);

  if (memcmp(header, "NAR", 3) != 0 || header[3] != 0x01) {
    // TODO: Create a more specific exception type.
    throw std::exception();
  }

  uint32_t num_files;
  fread(&num_files, sizeof(uint32_t), 1, this->base_file);

  for (uint32_t i = 0; i < num_files; i++) {

    uint32_t file_name_length;
    fread(&file_name_length, 4, 1, this->base_file);
    uint64_t file_length;
    fread(&file_length, 8, 1, this->base_file);

    uint8_t file_metadata[8];
    fread(file_metadata, 1, 8, this->base_file);

    char* file_name = new char[file_name_length];
    fread(file_name, 1, file_name_length, this->base_file);

    this->file_cache[std::string(file_name)] = {(uint64_t)ftell(this->base_file), file_length};

    delete[] file_name;

  }

}

mount_nar_t::~mount_nar_t() {
  fclose(this->base_file);
}

file_base_t* mount_nar_t::open_file(std::string path) {
  for (auto i = file_cache.begin(); i != file_cache.end(); i++) {
    if (i->first == path) {
      file_nar_t* file = new file_nar_t(i->second.offset, i->second.size, this->base_file);
      return file;
    }
  }
  return nullptr;
}

}
