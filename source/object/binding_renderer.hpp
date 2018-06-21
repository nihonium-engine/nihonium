#ifndef NH_OBJECT_BINDING_RENDERER_H
#define NH_OBJECT_BINDING_RENDERER_H

#include "../../external/duktape/duktape.h"

#include "../renderer/renderer_base.hpp"

namespace nh {

void duk_bind_renderer(duk_context* ctx);

}

#endif
