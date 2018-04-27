#ifndef NH_FILE_READER_NAR_H
#define NH_FILE_READER_NAR_H

#include <cstring>

#include "file_reader_base.hpp"

namespace nh {

class file_reader_nar_t : public file_reader_base_t  {

  public:

  file_reader_nar_t(std::string file, file_reader_base_t* source_reader);

  size_t read_bytes(size_t num_bytes, uint8_t* destination);
  void set_pos_absolute(size_t pos);
  void set_pos_forwards(size_t pos);
  void set_pos_backwards(size_t pos);
  size_t get_pos();

  private:

  uint64_t file_start_offset;
  uint64_t offset_in_file;
  uint64_t file_length;
  uint8_t compression_format;
  file_reader_base_t* source_reader;

};

}

#endif