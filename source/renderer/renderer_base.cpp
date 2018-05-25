#include "renderer_base.hpp"

namespace nh {

void renderer_base_t::add_to_render_queue(render_queue_item_t item) {
  this->render_queue.push_back(item);
}

}
