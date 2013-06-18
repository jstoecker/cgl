#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "shader.h"

using namespace cgl;

namespace cgl
{
  struct GLShaderObject
  {
    GLuint id;
    GLenum type;
    std::string source;
  };
  
  GLShaderObject* getShaderObject(GLuint id)
  {
    static std::map<GLuint, GLShaderObject> objects;
    if (objects.find(id) == objects.end()) {
      GLShaderObject obj = {id, 0, ""};
      objects[id] = obj;
    }
    return &objects[id];
  }
  
  std::ostream& operator<<(std::ostream& os, const Shader& shader)
  {
    os << "Shader: id = " << shader.id();
    os << ", type = " << shader.type();
    return os;
  }
}

Shader::Shader() : obj_(0)
{
}

Shader::Shader(GLuint id) : obj_(getShaderObject(id))
{
}

GLuint Shader::id() const
{
  return (obj_ ? obj_->id : 0);
}

GLenum Shader::type() const
{
  return (obj_ ? obj_->type : 0);
}

std::string Shader::source() const
{
  return (obj_ ? obj_->source : std::string());
}

std::string Shader::log() const
{
  if (!obj_)
    return std::string();
  
  GLint maxLength = 0;
  glGetShaderiv(obj_->id, GL_INFO_LOG_LENGTH, &maxLength);
  GLchar* buf = new GLchar[maxLength];
  
  glGetShaderInfoLog(obj_->id, maxLength, &maxLength, buf);
  std::string log(buf);
  delete[] buf;
  
  return log;
}

bool Shader::compile(const char* src, GLenum type)
{
  if (!obj_)
    obj_ = getShaderObject(glCreateShader(type));
  
  obj_->type = type;
  obj_->source = std::string(src);
  
  glShaderSource(obj_->id, 1, &src, NULL);
  glCompileShader(obj_->id);
  
  GLint status;
  glGetShaderiv(obj_->id, GL_COMPILE_STATUS, &status);
  
  if (!status)
    glDelete();
  
  return status;
}

bool Shader::compileFile(const char* fileName, GLenum type)
{
  std::ifstream in(fileName);
  std::string src((std::istreambuf_iterator<char>(in)),
                  std::istreambuf_iterator<char>());
  return compile(src.c_str(), type);
}

void Shader::glDelete()
{
  if (obj_) {
    glDeleteShader(obj_->id);
    obj_ = NULL;
  }
}
