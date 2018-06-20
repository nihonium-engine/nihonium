#include "binding_log.hpp"

namespace nh {

static duk_ret_t bind_log_info(duk_context* ctx) {

  global_logger->log_info("%s", duk_to_string(ctx, 0));

  return 0;
}

static duk_ret_t bind_log_warning(duk_context* ctx) {

  global_logger->log_warning("%s", duk_to_string(ctx, 0));

  return 0;
}

static duk_ret_t bind_log_error(duk_context* ctx) {

  global_logger->log_error("%s", duk_to_string(ctx, 0));

  return 0;
}

void duk_bind_log(duk_context* ctx) {

  duk_idx_t object = duk_push_object(ctx);

  duk_push_c_function(ctx, bind_log_info, 1);
  duk_put_prop_string(ctx, object, "log_info");

  duk_push_c_function(ctx, bind_log_warning, 1);
  duk_put_prop_string(ctx, object, "log_warning");

  duk_push_c_function(ctx, bind_log_error, 1);
  duk_put_prop_string(ctx, object, "log_error");

  duk_put_global_string(ctx, "log");

}

}
