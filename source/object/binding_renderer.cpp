#include "binding_renderer.hpp"

namespace nh {

static duk_ret_t bind_render(duk_context* ctx) {

  duk_get_prop_string(ctx, 0, "ptr");
  model_t* model = (model_t*)duk_get_pointer(ctx, -1);

  duk_get_prop_string(ctx, 1, "ptr");
  material_t* material = (material_t*)duk_get_pointer(ctx, -1);

  duk_get_prop_index(ctx, 2, 0);
  float pos_x = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 2, 1);
  float pos_y = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 2, 2);
  float pos_z = duk_to_number(ctx, -1);

  duk_get_prop_index(ctx, 3, 0);
  float rot_x = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 3, 1);
  float rot_y = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 3, 2);
  float rot_z = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 3, 2);
  float rot_w = duk_to_number(ctx, -1);

  duk_get_prop_index(ctx, 4, 0);
  float scale_x = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 4, 1);
  float scale_y = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 4, 2);
  float scale_z = duk_to_number(ctx, -1);

  duk_pop_n(ctx, 10);

  render_queue_item_t item;
  item.model = model;
  item.material = material;
  item.position = HMM_Vec3(pos_x, pos_y, pos_z);
  item.rotation = HMM_Quaternion(rot_x, rot_y, rot_z, rot_w);
  item.scale = HMM_Vec3(scale_x, scale_y, scale_z);
  global_renderer->add_to_render_queue(item);

  return 0;
  
}

void duk_bind_renderer(duk_context* ctx) {

  duk_idx_t object = duk_push_object(ctx);

  duk_push_c_function(ctx, bind_render, 5);
  duk_put_prop_string(ctx, object, "render");

  duk_put_global_string(ctx, "render");

}

}
