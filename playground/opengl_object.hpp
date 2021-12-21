#ifndef OPENGL_OBJECT_HPP
#define OPENGL_OBJECT_HPP

#include <GL/glew.h>

// This looks like C++ black magic
// https://stackoverflow.com/a/17161788

struct VertexArrayObjectTraits {
  typedef GLuint value_type;

  static value_type Create() {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    return vao;
  };

  static void Destroy(value_type vao) { glDeleteVertexArrays(1, &vao); };
};

struct BufferObjectTraits {
  typedef GLuint value_type;

  static value_type Create() {
    GLuint buf;
    glGenBuffers(1, &buf);
    glBindBuffer(GL_ARRAY_BUFFER, buf);
    return buf;
  };

  static void Destroy(value_type buf) { glDeleteBuffers(1, &buf); };
};

template <typename T>
class OpenGLObject {
 public:
  OpenGLObject() : m_obj(T::Create()) {}
  ~OpenGLObject() { T::Destroy(m_obj); }

  operator typename T::value_type() { return m_obj; }

 private:
  typename T::value_type m_obj;
};

#endif
