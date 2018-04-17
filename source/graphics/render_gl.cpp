#include "render_gl.hpp"

namespace nh {

void GLRender::add_to_queue(RenderCommand* command) {

  commands.push_back(command);

}

void GLRender::render() {



}
  
}