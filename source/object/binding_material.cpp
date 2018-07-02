#include "binding_material.hpp"

namespace nh {

static duk_ret_t destroy_material(duk_context* ctx) {

  duk_get_prop_string(ctx, 0, "ptr");

  material_t* material = (material_t*)duk_get_pointer(ctx, -1);

  if (material) {
    delete material;
  }

  return 0;

}

static duk_ret_t bind_load_material(duk_context* ctx) {

  duk_get_prop_string(ctx, 0, "ptr");

  file_base_t* file = (file_base_t*)duk_get_pointer(ctx, -1);

  material_t* material = load_material(file);

  duk_idx_t object = duk_push_object(ctx);

  duk_push_pointer(ctx, material);
  duk_put_prop_string(ctx, object, "ptr");

  duk_push_c_function(ctx, destroy_material, 1);
  duk_set_finalizer(ctx, object);

  return 1;
  
}

void duk_bind_material(duk_context* ctx) {

  duk_idx_t object = duk_push_object(ctx);

  duk_push_c_function(ctx, bind_load_material, 1);
  duk_put_prop_string(ctx, object, "load");

  duk_put_global_string(ctx, "material");

}

}
