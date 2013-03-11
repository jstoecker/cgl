#ifndef CGL_TEXTURE_H_
#define CGL_TEXTURE_H_

#include "cgl.h"

namespace cgl
{
  struct GLTextureObject;

  class Texture
  {
  public:
    Texture();
    
    Texture(const Texture&);
    
    Texture(GLuint id);
    
    GLuint id() const;
    
    /// Returns the texture width.
    GLuint width() const;
    
    /// Returns the texture height. Has no relevance for 1D textures.
    GLuint height() const;
    
    /// Returns the texture depth. Has no relevance for 1D or 2D textures.
    GLuint depth() const;
    
    /// Returns the current texture target (1D, 2D, 3D...)
    GLenum target() const;
    
    /// Binds the referenced texture object to its target.
    void bind() const;
    
    /// Unbinds the referenced texture object from its target.
    void unbind() const;
    
    /// Creates a new OpenGL texture object and makes this reference it.
    void generate(GLenum target);
    
    void setData2D(GLint level,
                   GLint internalFormat,
                   GLsizei width,
                   GLsizei height,
                   GLenum format,
                   GLenum type,
                   const GLvoid* data);
    
    void setData2D(GLint internalFormat,
                   GLsizei width,
                   GLsizei height,
                   GLenum format,
                   GLenum type,
                   const GLvoid* data);
    
    void setParameter(GLenum pname, GLint param);
    
    void setParameter(GLenum pname, GLfloat param);
    
    /// Deletes the OpenGL texture object referenced by this.
    void glDelete();
    
  private:
    GLTextureObject* obj_;    
  };
  
} // namespace cgl

#endif // CGL_TEXTURE_H_
