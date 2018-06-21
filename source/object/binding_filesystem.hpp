#ifndef NH_OBJECT_BINDING_FILESYSTEM_H
#define NH_OBJECT_BINDING_FILESYSTEM_H

#include "../../external/duktape/duktape.h"

#include "../filesystem/filesystem.hpp"

namespace nh {

void duk_bind_filesystem(duk_context* ctx);

}

#endif
