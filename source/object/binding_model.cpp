#include "binding_model.hpp"

namespace nh {

static duk_ret_t destroy_model(duk_context* ctx) {

  duk_get_prop_string(ctx, 0, "ptr");

  model_t* model = (model_t*)duk_get_pointer(ctx, -1);

  if (model) {
    delete model;
  }

  return 0;

}

static duk_ret_t bind_load_model(duk_context* ctx) {

  duk_get_prop_string(ctx, 0, "ptr");

  file_base_t* file = (file_base_t*)duk_get_pointer(ctx, -1);

  model_t* model = global_model_factory->load_model(file);

  duk_idx_t object = duk_push_object(ctx);

  duk_push_pointer(ctx, model);
  duk_put_prop_string(ctx, object, "ptr");

  duk_push_c_function(ctx, destroy_model, 1);
  duk_set_finalizer(ctx, object);

  return 1;
  
}

void duk_bind_model(duk_context* ctx) {

  duk_idx_t object = duk_push_object(ctx);

  duk_push_c_function(ctx, bind_load_model, 1);
  duk_put_prop_string(ctx, object, "load");

  duk_put_global_string(ctx, "model");

}

}
