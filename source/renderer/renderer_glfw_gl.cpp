#include "renderer_glfw_gl.hpp"

namespace nh {

renderer_glfw_gl_t::renderer_glfw_gl_t() {

  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  this->window = glfwCreateWindow(800, 600, "Nihonium Engine", NULL, NULL);

  if (!window) {
    // TODO: Error.
  }

  glfwMakeContextCurrent(this->window);

  glfwSwapInterval(1);

  gladLoadGL();

  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_BLEND);
  //glEnable(GL_MULTISAMPLE);
  //glEnable(GL_CULL_FACE);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void renderer_glfw_gl_t::frame_start() {
  glfwSwapBuffers(this->window);
  glfwPollEvents();

  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderer_glfw_gl_t::render() {
  for (auto i = this->render_queue.begin(); i != this->render_queue.end(); i++) {

    shader_gl_t* shader = dynamic_cast<shader_gl_t*>(i->shader);
    if (!shader) {
      // TODO: Log error.
      printf("Shader wasn't an OpenGL shader.\n");
    }

    glUseProgram(shader->program);

    hmm_mat4 model_matrix = HMM_Translate(HMM_Vec3(0.0f, 0.0f, -3.0f));
    hmm_mat4 projection_matrix = HMM_Perspective(45.0f, 800.0f / 600.0f, 0.01f, 1000.0f);
  
    GLint model_location = glGetUniformLocation(shader->program, "nh_model");
    glUniformMatrix4fv(model_location, 1, GL_FALSE, (const GLfloat*)&model_matrix);

    GLint projection_location = glGetUniformLocation(shader->program, "nh_projection");
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, (const GLfloat*)&projection_matrix);

    for (auto j = i->model->meshes.begin(); j != i->model->meshes.end(); j++) {
      mesh_gl_t* mesh = dynamic_cast<mesh_gl_t*>(*j);
      if (!mesh) {
        // TODO: Log error.
        printf("Mesh wasn't an OpenGL mesh.\n");
      }

      glBindVertexArray(mesh->vao);
    
      glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
    }

  }
  this->render_queue.clear();
}

renderer_glfw_gl_t::~renderer_glfw_gl_t() {

  glfwDestroyWindow(window);

  glfwTerminate();

}

}
