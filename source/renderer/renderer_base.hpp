#ifndef NH_RENDERER_BASE_H
#define NH_RENDERER_BASE_H

#include <vector>

#include "../../external/hmm/HandmadeMath.h"

#include "../model/model.hpp"
#include "../shader/shader_base.hpp"

namespace nh {

struct render_queue_item_t {
  model_t* model;
  shader_base_t* shader;
  hmm_vec3 position;
  hmm_quaternion rotation;
  hmm_vec3 scale;
  int layer;
};

class renderer_base_t {

    public:
    virtual void frame_start() = 0;

    void add_to_render_queue(render_queue_item_t item);

    virtual void render() = 0;

    protected:
    std::vector<render_queue_item_t> render_queue;

};
  
}

#endif
