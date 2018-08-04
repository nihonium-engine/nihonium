#include "object.hpp"

namespace nh {

void object_t::update(double delta_time) {

  for (auto i = this->scripts.begin(); i != this->scripts.end(); i++) {

    duk_get_global_string(i->second, "update");
    duk_push_number(i->second, delta_time);
    duk_call(i->second, 1);
    duk_pop(i->second);

  }


}

void object_t::draw() {

  for (auto i = this->scripts.begin(); i != this->scripts.end(); i++) {

    duk_get_global_string(i->second, "draw");
    duk_call(i->second, 0);
    duk_pop(i->second);

  }

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
  duk_bind_filesystem(ctx);
  duk_bind_material(ctx);
  duk_bind_model(ctx);
  duk_bind_shader(ctx);
  duk_bind_renderer(ctx);
  duk_bind_maths(ctx);
  duk_bind_input(ctx);

  duk_push_string(ctx, script_source);
  duk_push_string(ctx, file_name.c_str());
  duk_compile(ctx, 0);
  duk_call(ctx, 0);

  delete [] script_source;

  this->scripts[file_name] = ctx;

}

}