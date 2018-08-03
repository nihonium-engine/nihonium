#include "binding_maths.hpp"

namespace nh {

static duk_ret_t bind_vec3_new(duk_context* ctx) {

  float x = duk_to_number(ctx, 0);
  float y = duk_to_number(ctx, 1);
  float z = duk_to_number(ctx, 2);

  duk_idx_t array_index = duk_push_array(ctx);
  duk_push_number(ctx, x);
  duk_put_prop_index(ctx, array_index, 0);
  duk_push_number(ctx, y);
  duk_put_prop_index(ctx, array_index, 1);
  duk_push_number(ctx, z);
  duk_put_prop_index(ctx, array_index, 2);

  return 1;
}

static duk_ret_t bind_vec3_add(duk_context* ctx) {

  duk_get_prop_index(ctx, 0, 0);
  float left_x = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 0, 1);
  float left_y = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 0, 2);
  float left_z = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 1, 0);
  float right_x = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 1, 1);
  float right_y = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 1, 2);
  float right_z = duk_to_number(ctx, -1);
  duk_pop_n(ctx, 6);

  duk_idx_t array_index = duk_push_array(ctx);
  duk_push_number(ctx, left_x + right_x);
  duk_put_prop_index(ctx, array_index, 0);
  duk_push_number(ctx, left_y + right_y);
  duk_put_prop_index(ctx, array_index, 1);
  duk_push_number(ctx, left_z + right_z);
  duk_put_prop_index(ctx, array_index, 2);

  return 1;
}

static duk_ret_t bind_vec3_sub(duk_context* ctx) {

  duk_get_prop_index(ctx, 0, 0);
  float left_x = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 0, 1);
  float left_y = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 0, 2);
  float left_z = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 1, 0);
  float right_x = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 1, 1);
  float right_y = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 1, 2);
  float right_z = duk_to_number(ctx, -1);
  duk_pop_n(ctx, 6);

  duk_idx_t array_index = duk_push_array(ctx);
  duk_push_number(ctx, left_x - right_x);
  duk_put_prop_index(ctx, array_index, 0);
  duk_push_number(ctx, left_y - right_y);
  duk_put_prop_index(ctx, array_index, 1);
  duk_push_number(ctx, left_z - right_z);
  duk_put_prop_index(ctx, array_index, 2);

  return 1;
}

static duk_ret_t bind_vec3_mul(duk_context* ctx) {

  duk_get_prop_index(ctx, 0, 0);
  float left_x = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 0, 1);
  float left_y = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 0, 2);
  float left_z = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 1, 0);
  float right_x = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 1, 1);
  float right_y = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 1, 2);
  float right_z = duk_to_number(ctx, -1);
  duk_pop_n(ctx, 6);

  duk_idx_t array_index = duk_push_array(ctx);
  duk_push_number(ctx, left_x * right_x);
  duk_put_prop_index(ctx, array_index, 0);
  duk_push_number(ctx, left_y * right_y);
  duk_put_prop_index(ctx, array_index, 1);
  duk_push_number(ctx, left_z * right_z);
  duk_put_prop_index(ctx, array_index, 2);

  return 1;
}

static duk_ret_t bind_vec3_div(duk_context* ctx) {

  duk_get_prop_index(ctx, 0, 0);
  float left_x = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 0, 1);
  float left_y = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 0, 2);
  float left_z = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 1, 0);
  float right_x = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 1, 1);
  float right_y = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 1, 2);
  float right_z = duk_to_number(ctx, -1);
  duk_pop_n(ctx, 6);

  duk_idx_t array_index = duk_push_array(ctx);
  duk_push_number(ctx, left_x / right_x);
  duk_put_prop_index(ctx, array_index, 0);
  duk_push_number(ctx, left_y / right_y);
  duk_put_prop_index(ctx, array_index, 1);
  duk_push_number(ctx, left_z / right_z);
  duk_put_prop_index(ctx, array_index, 2);

  return 1;
}

static duk_ret_t bind_vec3_len(duk_context* ctx) {

  duk_get_prop_index(ctx, 0, 0);
  float left_x = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 0, 1);
  float left_y = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 0, 2);
  float left_z = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 1, 0);
  duk_pop_n(ctx, 3);

  duk_push_number(ctx, sqrt(left_x * left_x + left_y * left_y + left_z * left_z));

  return 1;
}

static duk_ret_t bind_vec3_len_squared(duk_context* ctx) {

  duk_get_prop_index(ctx, 0, 0);
  float left_x = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 0, 1);
  float left_y = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 0, 2);
  float left_z = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 1, 0);
  duk_pop_n(ctx, 3);

  duk_push_number(ctx, left_x * left_x + left_y * left_y + left_z * left_z);

  return 1;
}

static duk_ret_t bind_quat_new(duk_context* ctx) {

  float x = duk_to_number(ctx, 0);
  float y = duk_to_number(ctx, 1);
  float z = duk_to_number(ctx, 2);
  float w = duk_to_number(ctx, 3);

  duk_idx_t array_index = duk_push_array(ctx);
  duk_push_number(ctx, x);
  duk_put_prop_index(ctx, array_index, 0);
  duk_push_number(ctx, y);
  duk_put_prop_index(ctx, array_index, 1);
  duk_push_number(ctx, z);
  duk_put_prop_index(ctx, array_index, 2);
  duk_push_number(ctx, w);
  duk_put_prop_index(ctx, array_index, 3);

  return 1;
}

static duk_ret_t bind_quat_from_euler(duk_context* ctx) {

  float in_x = duk_to_number(ctx, 0);
  float in_y = duk_to_number(ctx, 1);
  float in_z = duk_to_number(ctx, 2);

  float cos_x = cos(in_x / 2);
  float sin_x = sin(in_x / 2);

  float cos_y = cos(in_y / 2);
  float sin_y = sin(in_y / 2);

  float cos_z = cos(in_z / 2);
  float sin_z = sin(in_z / 2);

  duk_idx_t array_index = duk_push_array(ctx);
  duk_push_number(ctx, cos_x * cos_y * cos_z - sin_x * sin_y * cos_z);
  duk_put_prop_index(ctx, array_index, 0);
  duk_push_number(ctx, sin_x * cos_y * sin_z + cos_x * sin_y * sin_z);
  duk_put_prop_index(ctx, array_index, 1);
  duk_push_number(ctx, cos_x * sin_y * cos_z - sin_x * cos_y * sin_z);
  duk_put_prop_index(ctx, array_index, 2);
  duk_push_number(ctx, cos_x * cos_y * cos_z + sin_x * sin_y * sin_z);
  duk_put_prop_index(ctx, array_index, 3);

  return 1;
}

static duk_ret_t bind_quat_mul(duk_context* ctx) {

  duk_get_prop_index(ctx, 0, 0);
  float left_x = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 0, 1);
  float left_y = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 0, 2);
  float left_z = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 0, 3);
  float left_w = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 1, 0);
  float right_x = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 1, 1);
  float right_y = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 1, 2);
  float right_z = duk_to_number(ctx, -1);
  duk_get_prop_index(ctx, 0, 3);
  float right_w = duk_to_number(ctx, -1);
  duk_pop_n(ctx, 6);

  duk_idx_t array_index = duk_push_array(ctx);
  duk_push_number(ctx, (left_x * right_w) + (left_y * right_z) - (left_z * right_y) + (left_w * right_x));
  duk_put_prop_index(ctx, array_index, 0);
  duk_push_number(ctx, (-left_x * right_z) + (left_y * right_w) + (left_z * right_x) + (left_w * right_y));
  duk_put_prop_index(ctx, array_index, 1);
  duk_push_number(ctx, (left_x * right_y) - (left_y * right_x) + (left_z * right_w) + (left_w * right_z));
  duk_put_prop_index(ctx, array_index, 2);
  duk_push_number(ctx, (-left_x * right_x) - (left_y * right_y) - (left_z * right_z) + (left_w * right_w));
  duk_put_prop_index(ctx, array_index, 3);

  return 1;
}

void duk_bind_maths(duk_context* ctx) {

  duk_idx_t vec3_object = duk_push_object(ctx);

  duk_push_c_function(ctx, bind_vec3_new, 3);
  duk_put_prop_string(ctx, vec3_object, "new");

  duk_push_c_function(ctx, bind_vec3_add, 2);
  duk_put_prop_string(ctx, vec3_object, "add");

  duk_push_c_function(ctx, bind_vec3_sub, 2);
  duk_put_prop_string(ctx, vec3_object, "sub");

  duk_push_c_function(ctx, bind_vec3_mul, 2);
  duk_put_prop_string(ctx, vec3_object, "mul");

  duk_push_c_function(ctx, bind_vec3_div, 2);
  duk_put_prop_string(ctx, vec3_object, "div");

  duk_push_c_function(ctx, bind_vec3_len, 1);
  duk_put_prop_string(ctx, vec3_object, "len");

  duk_push_c_function(ctx, bind_vec3_len_squared, 1);
  duk_put_prop_string(ctx, vec3_object, "len_squared");

  duk_put_global_string(ctx, "vec3");


  duk_idx_t quat_object = duk_push_object(ctx);

  duk_push_c_function(ctx, bind_quat_new, 4);
  duk_put_prop_string(ctx, quat_object, "new");

  duk_push_c_function(ctx, bind_quat_from_euler, 3);
  duk_put_prop_string(ctx, quat_object, "from_euler");

  duk_push_c_function(ctx, bind_quat_mul, 2);
  duk_put_prop_string(ctx, quat_object, "mul");

  duk_put_global_string(ctx, "quat");

}

}