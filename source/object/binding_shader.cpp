#include "binding_shader.hpp"

namespace nh {

static duk_ret_t destroy_shader(duk_context* ctx) {

  duk_get_prop_string(ctx, 0, "ptr");

  shader_base_t* shader = (shader_base_t*)duk_get_pointer(ctx, -1);

  if (shader) {
    delete shader;
  }

  return 0;

}

static duk_ret_t bind_load_shader(duk_context* ctx) {

  duk_get_prop_string(ctx, 0, "ptr");
  file_base_t* vert_file = (file_base_t*)duk_get_pointer(ctx, -1);

  duk_get_prop_string(ctx, 1, "ptr");
  file_base_t* frag_file = (file_base_t*)duk_get_pointer(ctx, -1);

  shader_base_t* shader = global_shader_factory->shader_create(vert_file, frag_file);

  duk_idx_t object = duk_push_object(ctx);

  duk_push_pointer(ctx, shader);
  duk_put_prop_string(ctx, object, "ptr");

  duk_push_c_function(ctx, destroy_shader, 1);
  duk_set_finalizer(ctx, object);

  return 1;
  
}

void duk_bind_shader(duk_context* ctx) {

  duk_idx_t object = duk_push_object(ctx);

  duk_push_c_function(ctx, bind_load_shader, 2);
  duk_put_prop_string(ctx, object, "load");

  duk_put_global_string(ctx, "shader");

}

}
