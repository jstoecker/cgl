#include "program.h"
#include <map>

using namespace cgl;

namespace cgl
{
  struct GLProgramObject
  {
    GLuint id;
    std::vector<Shader> shaders;
    std::map<std::string, Uniform> uniforms;
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
  
  std::ostream& operator<<(std::ostream& os, const Program& prog)
  {
    GLProgramObject* obj = prog.obj_;
    if (!obj)
      return os << "GLSL Program: EMPTY" << std::endl;
    
    os << "GLSL Program:" << std::endl;
    os << "Shaders:" << std::endl;
    for (unsigned i = 0; i < obj->shaders.size(); ++i)
      os << "  " << obj->shaders[i] << std::endl;
    os << "Uniforms:" << std::endl;
    for (std::map<std::string, Uniform>::iterator it = obj->uniforms.begin();
         it != obj->uniforms.end();
         ++it)
    {
      os << "  " << it->second << std::endl;
    }
    return os;
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

Uniform Program::uniform(const char* name) const
{
  return (obj_ ? obj_->uniforms[name] : Uniform());
}

std::vector<Uniform> Program::uniforms() const
{
  if (obj_) {
    std::vector<Uniform> buf;
    for (std::map<std::string, Uniform>::iterator it = obj_->uniforms.begin();
         it != obj_->uniforms.end();
         ++it)
    {
      buf.push_back(it->second);
    }
    return buf;
  }
  return std::vector<Uniform>();
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
  
  if (!status)
    return false;
  
  obj_->uniforms.clear();
  GLint numUniforms = 0;
  glGetProgramiv(obj_->id, GL_ACTIVE_UNIFORMS, &numUniforms);

  if (numUniforms > 0) {
    GLuint* uniformIDs = new GLuint[numUniforms];
    GLint bufSize = 0;
    glGetProgramiv(obj_->id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &bufSize);
    GLchar* buf = new GLchar[bufSize];
    
    for (int i = 0; i < numUniforms; ++i) {
      GLint size;
      GLenum type;
      glGetActiveUniform(obj_->id, i, bufSize, NULL, &size, &type, buf);
      GLint location = glGetUniformLocation(obj_->id, buf);
      std::string name = buf;
      obj_->uniforms[name] = Uniform(obj_->id, location, size, type, name);
    }
    delete[] uniformIDs;
    delete[] buf;
  }
  
  return true;
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

void Program::glDelete(bool deleteAttached)
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
