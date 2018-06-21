#include "binding_filesystem.hpp"

namespace nh {

static duk_ret_t destroy_file(duk_context* ctx) {

  duk_get_prop_string(ctx, 0, "ptr");

  file_base_t* file = (file_base_t*)duk_get_pointer(ctx, -1);

  if (file) {
    file->close();
    delete file;
  }

  return 0;
}

static duk_ret_t bind_filesystem_open(duk_context* ctx) {

  file_base_t* file = global_filesystem->open_file(duk_to_string(ctx, 0));

  duk_idx_t object = duk_push_object(ctx);

  duk_push_pointer(ctx, file);
  duk_put_prop_string(ctx, object, "ptr");

  duk_push_c_function(ctx, destroy_file, 1);
  duk_set_finalizer(ctx, object);

  return 1;

}

static duk_ret_t bind_filesystem_close(duk_context* ctx) {

  duk_get_prop_string(ctx, 0, "ptr");
  
  file_base_t* file = (file_base_t*)duk_get_pointer(ctx, -1);

  if (file) {
    file->close();
    delete file;
  }

  duk_push_pointer(ctx, nullptr);
  duk_put_prop_string(ctx, 0, "ptr");

  return 0;

}

void duk_bind_filesystem(duk_context* ctx) {

  duk_idx_t object = duk_push_object(ctx);

  duk_push_c_function(ctx, bind_filesystem_open, 1);
  duk_put_prop_string(ctx, object, "open");

  duk_push_c_function(ctx, bind_filesystem_close, 1);
  duk_put_prop_string(ctx, object, "close");

  duk_put_global_string(ctx, "filesystem");

}

}
