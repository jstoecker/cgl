#include "bitmap_font.h"

using namespace cgl;

// texture coordinate stepping based on 16x16 grid
static const float GLYPH_STEP = 0.0625f;

BitmapFont::BitmapFont(const Texture& texture) : texture_(texture)
{
  unsigned char glyphWidth = texture.width() / 16;
  for (int i = 0; i < 256; ++i)
    glyphWidths_[i] = glyphWidth;
  glyphHeight_ = texture.height() / 16;
}

BitmapFont::BitmapFont(const Texture& texture, const unsigned char* glyphWidths)
    : texture_(texture)
{
  for (int i = 0; i < 256; ++i)
    glyphWidths_[i] = glyphWidths[i];
  glyphHeight_ = texture.height() / 16;
}

void BitmapFont::begin(const Viewport& viewport)
{
/*
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  
  glOrtho(viewport.x, viewport.width, 0, viewport.height, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  
  texture_.bind();
  glBegin(GL_QUADS);
*/
}

void BitmapFont::end()
{
/*
  glEnd();
  texture_.unbind();
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
*/
}

void BitmapFont::drawString(const char* s, int x, int y)
{
/*
  // while (*s++)
  for (; *s; s++) {
    const char c = *s;    
    int glyphWidth = glyphWidths_[(unsigned)c];
        
    float uSize = (float)glyphWidth / texture_.width();
    float u = GLYPH_STEP * (c % 16);
    float v = 1.0f - GLYPH_STEP * (c / 16 + 1);
    
    glTexCoord2f(u, v);
    glVertex2f(x, y);
    
    glTexCoord2f(u + uSize, v);
    glVertex2f(x + glyphWidth, y);
    
    glTexCoord2f(u + uSize, v + GLYPH_STEP);
    glVertex2f(x + glyphWidth, y + glyphHeight_);
    
    glTexCoord2f(u, v + GLYPH_STEP);
    glVertex2f(x, y + glyphHeight_);

    x += glyphWidth;
  }
*/
}
