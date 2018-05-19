
#include "../file_reader/file_reader_stdio.hpp"
#include "../file_reader/file_reader_nar.hpp"

#include "../renderer/renderer_glfw_gl.hpp"

#include "../model/mesh_gl.hpp"
#include "../model/model_factory.hpp"

#include <cstdio>

int main(int argc, char** argv) {

  (void)argc; (void)argv;

  nh::renderer_glfw_gl_t* renderer = new nh::renderer_glfw_gl_t();

  nh::model_factory_t* model_factory = new nh::model_factory_t();

  nh::file_reader_stdio_t* reader = new nh::file_reader_stdio_t("test.nmdl");

  nh::model_t* model = model_factory->load_model<nh::mesh_gl_t>(reader);

  while (true) {
    renderer->frame_start();
    for (size_t i = 0; i < model->meshes.size(); i++) {
      dynamic_cast<nh::mesh_gl_t*>(model->meshes[i])->temp_draw();
    }
  }

  return 0;

}
