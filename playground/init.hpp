#ifndef HI_HPP
#define HI_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <iostream>

extern GLFWwindow* window;

inline void initializeGLFW() {
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    std::exit(-1);
  }
}

inline void setWindowHints() {
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
                 GL_TRUE);  // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

inline void createWindow() {
  // Open a window and create its OpenGL context
  window = glfwCreateWindow(1024, 768, "Playground nice", NULL, NULL);
  if (window == NULL) {
    std::cerr
        << "Failed to open GLFW window. If you have an Intel GPU, they are "
           "not 3.3 compatible. Try the 2.1 version of the tutorials.\n";
    glfwTerminate();
    std::exit(-1);
  }
  glfwMakeContextCurrent(window);
}

inline void initializeGLEW() {
  glewExperimental = true;
  // Initialize GLEW
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW\n";
    glfwTerminate();
    std::exit(-1);
  }
}

inline void initWindow() {
  initializeGLFW();
  setWindowHints();
  createWindow();
  initializeGLEW();

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // Dark blue background
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
}

#endif