#ifndef NH_OBJECT_BINDING_CAMERA_H
#define NH_OBJECT_BINDING_CAMERA_H

#include "../../external/duktape/duktape.h"

#include "../camera/camera.hpp"

namespace nh {

void duk_bind_camera(duk_context* ctx);

}

#endif
