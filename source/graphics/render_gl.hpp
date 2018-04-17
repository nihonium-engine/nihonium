#ifndef NH_RENDER_GL_H
#define NH_RENDER_GL_H

#include <vector>

#include "render_base.hpp"

namespace nh {

class GLRender : public BaseRender {

  public:

  void add_to_queue(RenderCommand* command);

  void render();

  private:

  std::vector<RenderCommand*> commands;

};
 
}

#endif