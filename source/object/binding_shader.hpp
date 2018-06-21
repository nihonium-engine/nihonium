#ifndef NH_OBJECT_BINDING_SHADER_H
#define NH_OBJECT_BINDING_SHADER_H

#include "../../external/duktape/duktape.h"

#include "../shader/shader_base.hpp"

namespace nh {

void duk_bind_shader(duk_context* ctx);

}

#endif
