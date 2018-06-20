#ifndef NH_OBJECT_BINDING_LOG_H
#define NH_OBJECT_BINDING_LOG_H

#include "../../external/duktape/duktape.h"

#include "../log/logger.hpp"

namespace nh {

void duk_bind_log(duk_context* ctx);

}

#endif
