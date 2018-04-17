#ifndef NH_RENDER_BASE_H
#define NH_RENDER_BASE_H

namespace nh {

struct RenderCommand {



};

class BaseRender {

  public:

  virtual void add_to_queue(RenderCommand* command) = 0;

};

}

#endif