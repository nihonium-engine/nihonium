#ifndef NH_BINDING_MATERIAL_H
#define NH_BINDING_MATERIAL_H

#include "../../external/duktape/duktape.h"

#include "../material/material.hpp"

namespace nh {

void duk_bind_material(duk_context* ctx);

}

#endif
