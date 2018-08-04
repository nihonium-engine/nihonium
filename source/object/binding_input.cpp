#include "binding_input.hpp"

namespace nh {

static duk_ret_t bind_is_down(duk_context* ctx) {
  std::string key = duk_to_string(ctx, 0);
  duk_push_boolean(ctx, global_input->is_down(key));
  return 1;
}

void duk_bind_input(duk_context* ctx) {

  duk_idx_t object = duk_push_object(ctx);

  duk_push_c_function(ctx, bind_is_down, 1);
  duk_put_prop_string(ctx, object, "is_down");

  duk_put_global_string(ctx, "input");

}

}
