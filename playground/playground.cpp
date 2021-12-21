#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <common/shader.hpp>
#include <cstdlib>
#include <iostream>

GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "init.hpp"
#include "opengl_object.hpp"

inline glm::mat4 createMVP(float width, float height) {
  glm::mat4 Projection =
      glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);

  glm::mat4 View =
      glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

  glm::mat4 Model = glm::mat4(1.0f);
  return Projection * View * Model;
}

int main(void) {
  // Not in the scope of this lesson anymore
  initWindow();

  auto vertexArray = OpenGLObject<VertexArrayObjectTraits>();

  // Create and compile our GLSL program from the shaders
  GLuint programID = LoadShaders("simple.v.glsl", "simple.f.glsl");

  glm::mat4 mvp = createMVP(4, 3);
  GLuint MatrixID = glGetUniformLocation(programID, "MVP");

  // clang-format off
  static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f,  0.0f,
     1.0f, -1.0f,  0.0f,
     0.0f,  1.0f,  0.0f,
  };
  // clang-format on

  auto vertexBuffer = OpenGLObject<BufferObjectTraits>();
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
               g_vertex_buffer_data, GL_STATIC_DRAW);

  do {
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(programID);

    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

  }  // Check if the ESC key was pressed or the window was closed
  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(window) == 0);

  glDeleteProgram(programID);

  // Close OpenGL window and terminate GLFW
  glfwTerminate();
  return 0;
}
