#include "object.hpp"

namespace nh {

void object_t::update(double delta_time) {

  (void)delta_time;

}

void object_t::draw() {

}

static void handle_fatal_error(void* userdata, const char* msg) {
  (void)userdata;
  global_logger->log_error("Script Error: %s", msg);
}

void object_t::add_script(std::string file_name) {

  file_base_t* file = global_filesystem->open_file(file_name);

  file->seek_end(0);
  size_t file_size = file->tell();
  file->seek_start(0);

  char* script_source = new char[file_size + 1];
  file->read(file_size, (uint8_t*)script_source);
  script_source[file_size] = '\0';

  file->close();

  duk_context* ctx = duk_create_heap(
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    handle_fatal_error
  );

  duk_bind_log(ctx);

  duk_push_string(ctx, script_source);
  duk_push_string(ctx, file_name.c_str());
  duk_compile(ctx, 0);
  duk_call(ctx, 0);

  delete [] script_source;

  this->scripts[file_name] = ctx;

}

}