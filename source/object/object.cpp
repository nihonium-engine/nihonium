#include "object.hpp"

namespace nh {

void object_t::update(double delta_time) {

  (void)delta_time;

}

void object_t::draw() {

}

static duk_ret_t test_print(duk_context* ctx) {
  printf("%s\n", duk_to_string(ctx, 0));
  return 0;
}

void object_t::add_script(std::string file_name) {

  file_base_t* file = filesystem->open_file(file_name);

  file->seek_end(0);
  size_t file_size = file->tell();
  file->seek_start(0);

  char* script_source = new char[file_size + 1];
  file->read(file_size, (uint8_t*)script_source);
  script_source[file_size] = '\0';

  file->close();

  duk_context* ctx = duk_create_heap_default();

  duk_push_c_function(ctx, test_print, 1);
  duk_put_global_string(ctx, "print");

  duk_push_string(ctx, script_source);
  duk_compile(ctx, 0);
  duk_call(ctx, 0);

  delete [] script_source;

  this->scripts[file_name] = ctx;

}

}