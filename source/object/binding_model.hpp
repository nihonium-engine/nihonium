#ifndef NH_OBJECT_BINDING_MODEL_H
#define NH_OBJECT_BINDING_MODEL_H

#include "../../external/duktape/duktape.h"

#include "../model/model.hpp"

namespace nh {

void duk_bind_model(duk_context* ctx);

}

#endif
