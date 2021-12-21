#ifndef CONSTS_HPP
#define CONSTS_HPP

#include <GL/glew.h>

#include <chrono>
#include <cstdlib>
#include <iostream>

// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive
// vertices give a triangle. A cube has 6 faces with 2 triangles each, so this
// makes 6*2=12 triangles, and 12*3 vertices
// clang-format off
static GLfloat g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
     1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
     1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
     1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
     1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
     1.0f,-1.0f, 1.0f
};
// clang-format on

// One color for each vertex.
static GLfloat g_color_buffer_data[12 * 3 * 3];

void changeColor(GLuint colorBuffer, GLfloat bufferData[], size_t size) {
  for (int v = 0; v < 12 * 3; ++v) {
    bufferData[3 * v + 0] = ((double)std::rand() / (RAND_MAX));
    bufferData[3 * v + 1] = ((double)std::rand() / (RAND_MAX));
    bufferData[3 * v + 2] = ((double)std::rand() / (RAND_MAX));
    bufferData[3 * v + 3] = ((double)std::rand() / (RAND_MAX));
  }
  glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
  glBufferData(GL_ARRAY_BUFFER, size, bufferData, GL_DYNAMIC_DRAW);
}

#endif
