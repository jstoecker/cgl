#include "program.h"
#include <map>

using namespace cgl;

namespace cgl
{
  struct GLProgramObject
  {
    GLuint id;
    std::vector<Shader> shaders;
    std::map<std::string, GLint> uniforms;
  };
  
  GLProgramObject* getProgramObj(GLuint id)
  {
    static std::map<GLuint, GLProgramObject> objects;
    if (objects.find(id) == objects.end()) {
      GLProgramObject obj = { id };
      objects[id] = obj;
    }
    return &objects[id];
  }
}

Program::Program() : obj_(0)
{
}

Program::Program(GLuint id) : obj_(getProgramObj(id))
{
}

GLuint Program::id() const
{
  return (obj_ ? obj_->id : 0);
}

std::string Program::log() const
{
  GLint maxLength = 0;
  glGetProgramiv(obj_->id, GL_INFO_LOG_LENGTH, &maxLength);
  GLchar* buf = new GLchar[maxLength];

  glGetProgramInfoLog(obj_->id, maxLength, &maxLength, buf);
  std::string log(buf);
  delete[] buf;

  return log;
}

std::vector<Shader> Program::shaders() const
{
  return (obj_ ? obj_->shaders : std::vector<Shader>());
}

GLint Program::getUniformLocation(const GLchar* name) const
{
  if (!obj_ || obj_->uniforms.find(name) == obj_->uniforms.end())
    return -1;
  return obj_->uniforms[name];
}

void Program::attach(const Shader& shader)
{
  if (!obj_)
    obj_ = getProgramObj(glCreateProgram());
  glAttachShader(obj_->id, shader.id());
  obj_->shaders.push_back(shader);
}

void Program::detach(const Shader& shader)
{
  if (obj_) {
    glDetachShader(obj_->id, shader.id());
    std::vector<Shader>::iterator it = obj_->shaders.begin();
    while (it != obj_->shaders.end()) { it++; }
    if (it != obj_->shaders.end())
      obj_->shaders.erase(it);
  }
}

void Program::detachAll()
{
  if (obj_) {
    std::vector<Shader>& attached = obj_->shaders;
    for (unsigned int i = 0; i < attached.size(); ++i)
      glDetachShader(obj_->id, attached[i].id());
    obj_->shaders.clear();
  }
}

bool Program::link()
{
  if (!obj_)
    return false;
  
  glLinkProgram(obj_->id);

  GLint status = 0;
  glGetProgramiv(obj_->id, GL_LINK_STATUS, &status);
  return status;
}

bool Program::validate() const
{
  if (obj_) {
    glValidateProgram(obj_->id);
    GLint status;
    glGetProgramiv(obj_->id, GL_VALIDATE_STATUS, &status);
    return status;
  }
  return false;
}

void Program::bind() const
{
  if (obj_)
    glUseProgram(obj_->id);
}

void Program::unbind() const
{
  glUseProgram(0);
}

void Program::release(bool deleteAttached)
{
  if (obj_) {
    if (deleteAttached) {
      std::vector<Shader>& attached = obj_->shaders;
      for (unsigned int i = 0; i < attached.size(); ++i) {
        glDetachShader(obj_->id, attached[i].id());
        attached[i].glDelete();
      }
    }
    glDeleteProgram(obj_->id);
    obj_->shaders.clear();
    obj_->uniforms.clear();
    obj_ = NULL;
  }
}

void Program::set(const GLchar* name, GLfloat x)
{
  glUniform1f(getUniformLocation(name), x);
}

void Program::set(const GLchar* name, GLfloat x, GLfloat y)
{
  glUniform2f(getUniformLocation(name), x, y);
}

void Program::set(const GLchar* name, GLfloat x, GLfloat y, GLfloat z)
{
  glUniform3f(getUniformLocation(name), x, y, z);
}

void Program::set(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
  glUniform4f(getUniformLocation(name), x, y, z, w);
}

void Program::set(const GLchar* name, const Vec2& v)
{
  glUniform2f(getUniformLocation(name), v.x, v.y);
}

void Program::set(const GLchar* name, const Vec3& v)
{
  glUniform3f(getUniformLocation(name), v.x, v.y, v.z);
}

void Program::set(const GLchar* name, const Vec4& v)
{
  glUniform4f(getUniformLocation(name), v.x, v.y, v.z, v.w);
}

void Program::set2(const GLchar* name, GLsizei count, const GLfloat* v)
{
  glUniform2fv(getUniformLocation(name), count, v);
}

void Program::set3(const GLchar* name, GLsizei count, const GLfloat* v)
{
  glUniform3fv(getUniformLocation(name), count, v);
}

void Program::set4(const GLchar* name, GLsizei count, const GLfloat* v)
{
  glUniform4fv(getUniformLocation(name), count, v);
}

void Program::set(const GLchar* name, GLint x)
{
  glUniform1i(getUniformLocation(name), x);
}

void Program::set(const GLchar* name, GLint x, GLint y)
{
  glUniform2i(getUniformLocation(name), x, y);
}

void Program::set(const GLchar* name, GLint x, GLint y, GLint z)
{
  glUniform3i(getUniformLocation(name), x, y, z);
}

void Program::set(const GLchar* name, GLint x, GLint y, GLint z, GLint w)
{
  glUniform4i(getUniformLocation(name), x, y, z, w);
}

void Program::set2(const GLchar* name, GLsizei count, const GLint* v)
{
  glUniform2iv(getUniformLocation(name), count, v);
}

void Program::set3(const GLchar* name, GLsizei count, const GLint* v)
{
  glUniform3iv(getUniformLocation(name), count, v);
}

void Program::set4(const GLchar* name, GLsizei count, const GLint* v)
{
  glUniform4iv(getUniformLocation(name), count, v);
}

void Program::set(const GLchar* name, const Mat4& m)
{
  glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, m);
}
