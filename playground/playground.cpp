#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <common/shader.hpp>
#include <cstdlib>
#include <iostream>

GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "data.hpp"
#include "init.hpp"
#include "opengl_object.hpp"

inline glm::mat4 createMVP(float width, float height, glm::vec3 center) {
  glm::mat4 Projection =
      glm::perspective(glm::radians(90.0f), width / height, 0.1f, 100.0f);

  glm::mat4 View =
      glm::lookAt(glm::vec3(4, 3, -3), center, glm::vec3(-1, 1, 0));

  glm::mat4 Model = glm::mat4(1.0f);
  return Projection * View * Model;
}

inline void changeColor() {}

int main(void) {
  // Not in the scope of this lesson anymore
  initWindow();

  auto vertexArray = OpenGLObject<VertexArrayObjectTraits>();

  // Create and compile our GLSL program from the shaders
  auto program = OpenGLProgram(LoadShaders("simple.v.glsl", "simple.f.glsl"));

  glm::mat4 cubeMVP = createMVP(4, 3, glm::vec3(0, 2, 1));
  glm::mat4 triangleMVP = createMVP(4, 3, glm::vec3(0, 3, -1));
  GLuint MatrixID = glGetUniformLocation(program, "MVP");

  auto vertexBuffer = OpenGLObject<BufferObjectTraits>();
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
               g_vertex_buffer_data, GL_STATIC_DRAW);

  // Enable depth test
  glEnable(GL_DEPTH_TEST);
  // Accept fragment if it closer to the camera than the former one
  glDepthFunc(GL_LESS);

  do {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);

    GLfloat bufferData[12 * 3 * 3];

    auto colorBuffer = OpenGLObject<BufferObjectTraits>();
    changeColor(colorBuffer, bufferData, sizeof(bufferData));

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &cubeMVP[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &triangleMVP[0][0]);

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

  // Close OpenGL window and terminate GLFW
  glfwTerminate();
  return 0;
}
