#include "binding_renderer.hpp"

namespace nh {

static duk_ret_t bind_render(duk_context* ctx) {

  duk_get_prop_string(ctx, 0, "ptr");
  model_t* model = (model_t*)duk_get_pointer(ctx, -1);

  duk_get_prop_string(ctx, 1, "ptr");
  shader_base_t* shader = (shader_base_t*)duk_get_pointer(ctx, -1);

  render_queue_item_t item;
  item.model = model;
  item.shader = shader;
  global_renderer->add_to_render_queue(item);

  return 0;
  
}

void duk_bind_renderer(duk_context* ctx) {

  duk_idx_t object = duk_push_object(ctx);

  duk_push_c_function(ctx, bind_render, 2);
  duk_put_prop_string(ctx, object, "render");

  duk_put_global_string(ctx, "render");

}

}
