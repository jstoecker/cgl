#ifndef CGL_SHADER_H_
#define CGL_SHADER_H_

#include <iostream>
#include <string>
#include "cgl.h"

namespace cgl
{
  struct GLShaderObject;
  
  /// GLSL shader object reference.
  class Shader
  {
  public:
    /// Creates a new empty shader reference.
    Shader();
    
    /// Creates a new shader reference.
    Shader(GLuint id);
    
    /// Returns the referenced shader's ID (0 if no shader referenced).
    GLuint id() const;
    
    /// Returns the type of the referenced shader (0 if no shader referenced).
    GLenum type() const;
    
    /// Returns the source code (empty string if no shader referenced).
    std::string source() const;
    
    /// Returns the error log from compiling (empty string if no errors).
    std::string log() const;
    
    /// Assigns source and compiles. Returns false if compiler errors. If this
    /// object does not yet reference a shader, a new one will be created.
    bool compile(const char* source, GLenum type);
    
    /// Assigns source from a file and compiles. Returns false if compiler
    /// errors. If this object does not yet reference a shader, a new one will
    /// be created.
    bool compileFile(const char* fileName, GLenum type);
    
    /// Deletes the referenced shader from the OpenGL context.
    void glDelete();
    
    /// Prints the shader ID and type.
    friend std::ostream& operator<<(std::ostream&, const Shader&);
    
  private:
    GLShaderObject* obj_;
  };
  
}

#endif // CGL_SHADER_H_
