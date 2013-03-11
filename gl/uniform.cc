#include "uniform.h"

using namespace cgl;

namespace cgl
{
  std::ostream& operator<<(std::ostream& os, const Uniform& uniform)
  {
    os << "Uniform: location = " << uniform.location();
    os << ", name = " << uniform.name();
    os << ", type = " << uniform.type();
    os << ", size = " << uniform.size();
    return os;
  }
}

Uniform::Uniform() : location_(0)
{}

Uniform::Uniform(GLuint program, GLint location, GLint size, GLenum type,
                 std::string name)
    : program_(program), location_(location), name_(name), size_(size),
      type_(type)
{}

GLint Uniform::location() const
{
  return location_;
}

GLint Uniform::size() const
{
  return size_;
}

GLenum Uniform::type() const
{
  return type_;
}

std::string Uniform::name() const
{
  return name_;
}

void Uniform::get(float* buf) const
{
  glGetUniformfv(program_, location_, buf);
}

void Uniform::get(int* buf) const
{
  glGetUniformiv(program_, location_, buf);
}

void Uniform::set(GLfloat x)
{
  glUniform1f(location_, x);
}

void Uniform::set(GLfloat x, GLfloat y)
{
  glUniform2f(location_, x, y);
}

void Uniform::set(GLfloat x, GLfloat y, GLfloat z)
{
  glUniform3f(location_, x, y, z);
}

void Uniform::set(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
  glUniform4f(location_, x, y, z, w);
}

void Uniform::set2(GLsizei count, const GLfloat* value)
{
  glUniform2fv(location_, count, value);
}

void Uniform::set3(GLsizei count, const GLfloat* value)
{
  glUniform3fv(location_, count, value); 
}

void Uniform::set4(GLsizei count, const GLfloat* value)
{
  glUniform4fv(location_, count, value);
}

void Uniform::set(const Vec2& value)
{
  glUniform2f(location_, value.x, value.y);
}

void Uniform::set(const Vec3& value)
{
  glUniform3f(location_, value.x, value.y, value.z);
}

void Uniform::set(const Vec4& value)
{
  glUniform4f(location_, value.x, value.y, value.z, value.w);
}

void Uniform::set(GLint x)
{
  glUniform1i(location_, x);
}

void Uniform::set(GLint x, GLint y)
{
  glUniform2i(location_, x, y);
}

void Uniform::set(GLint x, GLint y, GLint z)
{
  glUniform3i(location_, x, y, z);
}

void Uniform::set(GLint x, GLint y, GLint z, GLint w)
{
  glUniform4i(location_, x, y, z, w);
}

void Uniform::set2(GLsizei count, const GLint* value)
{
  glUniform2iv(location_, count, value);
}

void Uniform::set3(GLsizei count, const GLint* value)
{
  glUniform3iv(location_, count, value);
}

void Uniform::set4(GLsizei count, const GLint* value)
{
  glUniform4iv(location_, count, value);
}

void Uniform::set(const Mat4& matrix)
{
  glUniformMatrix4fv(location_, 1, GL_FALSE, matrix);
}
