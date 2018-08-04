#ifndef NH_OBJECT_BINDING_INPUT_H
#define NH_OBJECT_BINDING_INPUT_H

#include "../../external/duktape/duktape.h"

#include "../input/input_base.hpp"

namespace nh {

void duk_bind_input(duk_context* ctx);

}

#endif
