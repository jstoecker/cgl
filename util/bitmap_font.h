#ifndef GL_BITMAP_FONT_H_
#define GL_BITMAP_FONT_H_

#include "bitmap_image.h"
#include "cgl.h"

namespace cgl
{
  /// Renders text using a bitmap glyphs. The input glyph texture must be be
  /// formatted as a 16x16 glyph grid (256 total glyphs). The glyphs are matched
  /// to characters in row-major order. Glyphs must be evenly spaced; for
  /// example, a 512x384 texture would have glyphs of size 32x24. However,
  /// individual glyph widths can be given to indicate the portion of the glyph
  /// cell width used.
  class BitmapFont
  {
  public:
    /// Assumes monospaced font.
    BitmapFont(const Texture& texture);
    
    /// Font with variable-width glyphs. glyphWidths must have 256 elements.
    BitmapFont(const Texture& texture, const unsigned char* glyphWidths);
    
    void begin(const Viewport&);
    void end();
    void drawString(const char*, int x, int y);
    
  private:
    const Texture& texture_;
    unsigned char glyphWidths_[256];
    unsigned char glyphHeight_;
  };
  
}

#endif
