#include "texture.h"
#include <map>

using namespace cgl;

namespace cgl
{
  struct GLTextureObject
  {
    GLuint id;
    GLenum target;
    GLuint width;
    GLuint height;
    GLuint depth;
  };
  
  GLTextureObject* getTextureObj(GLuint id)
  {
    static std::map<GLuint, GLTextureObject> objects;
    if (objects.find(id) == objects.end()) {
      GLTextureObject obj = { id, 0, 0, 0, 0 };
      objects[id] = obj;
    }
    return &objects[id];
  }
}

Texture::Texture() : obj_(NULL)
{
}

Texture::Texture(GLuint id) : obj_(getTextureObj(id))
{
}

GLuint Texture::id() const
{
  return (obj_ ? obj_->id : 0);
}

GLuint Texture::width() const
{
  return (obj_ ? obj_->width : 0);
}

GLuint Texture::height() const
{
  return (obj_ ? obj_->height : 0);
}

GLuint Texture::depth() const
{
  return (obj_ ? obj_->depth : 0);
}

GLenum Texture::target() const
{
  return (obj_ ? obj_->target : 0);
}

void Texture::bind() const
{
  if (obj_)
    glBindTexture(obj_->target, obj_->id);
}

void Texture::unbind() const
{
  if (obj_)
    glBindTexture(obj_->target, 0);
}

void Texture::generate(GLenum target)
{
  GLuint newID;
  glGenTextures(1, &newID);
  obj_ = getTextureObj(newID);
  obj_->target = target;
}

void Texture::setData2D(GLint level,
                        GLint internalFormat,
                        GLsizei width,
                        GLsizei height,
                        GLenum format,
                        GLenum type,
                        const GLvoid *data)
{
  obj_->width = width;
  obj_->height = height;
  obj_->depth = 0;
  glTexImage2D(obj_->target, level, internalFormat, width, height, 0, format,
               type, data);
}

void Texture::setData2D(GLint internalFormat,
                        GLsizei width,
                        GLsizei height,
                        GLenum format,
                        GLenum type,
                        const GLvoid *data)
{
  setData2D(0, internalFormat, width, height, format, type, data);
}

void Texture::setParameter(GLenum pname, GLint param)
{
  glTexParameteri(obj_->target, pname, param);
}

void Texture::setParameter(GLenum pname, GLfloat param)
{
  glTexParameterf(obj_->target, pname, param);
}

void Texture::glDelete()
{
  if (obj_ && obj_->id)
    glDeleteTextures(1, &obj_->id);
}
