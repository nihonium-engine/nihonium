
#include "../file_reader/file_reader_stdio.hpp"
#include "../file_reader/file_reader_nar.hpp"

#include "../renderer/renderer_glfw_gl.hpp"

#include "../model/mesh_gl.hpp"
#include "../model/model_factory.hpp"

#include "../shader/shader_gl.hpp"

#include <cstdio>

int main(int argc, char** argv) {

  (void)argc; (void)argv;

  nh::renderer_glfw_gl_t* renderer = new nh::renderer_glfw_gl_t();

  nh::model_factory_t* model_factory = new nh::model_factory_t();

  nh::file_reader_stdio_t* reader = new nh::file_reader_stdio_t("test.nmdl");

  nh::file_reader_stdio_t* vert_reader = new nh::file_reader_stdio_t("vert.vert");
  nh::file_reader_stdio_t* frag_reader = new nh::file_reader_stdio_t("frag.frag");

  nh::shader_factory_t* shader_factory = new nh::shader_factory_t();

  nh::shader_base_t* shader = shader_factory->shader_create<nh::shader_gl_t>(vert_reader, frag_reader);

  nh::model_t* model = model_factory->load_model<nh::mesh_gl_t>(reader);

  while (true) {
    renderer->frame_start();
    nh::render_queue_item_t item;
    item.model = model;
    item.shader = shader;
    renderer->add_to_render_queue(item);
    renderer->render();
  }

  return 0;

}
