#include "binding_camera.hpp"

namespace nh {


static duk_ret_t bind_new(duk_context* ctx) {
  std::string name = duk_to_string(ctx, 0);

  if (global_cameras.find(name) == global_cameras.end()) {
    camera_t camera = {
      0,
      0,
      1,
      1,
      HMM_Vec3(0, 0, 0),
      HMM_Quaternion(0, 0, 0, 1),
      false
    };
    global_cameras[name] = camera;
  }

  return 0;
}

// TODO: Error on invalid camera.
static duk_ret_t bind_set_position(duk_context* ctx) {
  std::string name = duk_to_string(ctx, 0);

  duk_get_prop_index(ctx, 1, 0);
  float pos_x = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 1, 1);
  float pos_y = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 1, 2);
  float pos_z = duk_to_number(ctx, -1);
  duk_pop_n(ctx, 3);

  global_cameras[name].position = HMM_Vec3(pos_x, pos_y, pos_z);

  return 0;
}

static duk_ret_t bind_set_rotation(duk_context* ctx) {
  std::string name = duk_to_string(ctx, 0);

  duk_get_prop_index(ctx, 1, 0);
  float rot_x = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 1, 1);
  float rot_y = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 1, 2);
  float rot_z = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 1, 3);
  float rot_w = duk_to_number(ctx, -1);
  duk_pop_n(ctx, 4);

  global_cameras[name].rotation = HMM_Quaternion(rot_x, rot_y, rot_z, rot_w);

  return 0;
}

static duk_ret_t bind_set_enabled(duk_context* ctx) {
  std::string name = duk_to_string(ctx, 0);

  bool enabled = duk_to_boolean(ctx, 1);

  global_cameras[name].enabled = enabled;

  return 0;
}

static duk_ret_t bind_set_screen_pos(duk_context* ctx) {
  std::string name = duk_to_string(ctx, 0);

  float pos_x = duk_to_number(ctx, 1);
  float pos_y = duk_to_number(ctx, 2);
  float size_x = duk_to_number(ctx, 3);
  float size_y = duk_to_number(ctx, 4);

  global_cameras[name].screen_x = pos_x;
  global_cameras[name].screen_y = pos_y;
  global_cameras[name].screen_width = size_x;
  global_cameras[name].screen_height = size_y;

  return 0;
}

void duk_bind_camera(duk_context* ctx) {

  duk_idx_t object = duk_push_object(ctx);

  duk_push_c_function(ctx, bind_new, 1);
  duk_put_prop_string(ctx, object, "new");

  duk_push_c_function(ctx, bind_set_position, 2);
  duk_put_prop_string(ctx, object, "set_position");

  duk_push_c_function(ctx, bind_set_rotation, 2);
  duk_put_prop_string(ctx, object, "set_rotation");

  duk_push_c_function(ctx, bind_set_enabled, 2);
  duk_put_prop_string(ctx, object, "set_enabled");

  duk_push_c_function(ctx, bind_set_screen_pos, 5);
  duk_put_prop_string(ctx, object, "set_screen_pos");

  duk_put_global_string(ctx, "camera");

}

}
