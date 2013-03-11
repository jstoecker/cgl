#ifndef CGL_TEXT_RENDERER_H_
#define CGL_TEXT_RENDERER_H_

#include <map>
#include <string>
#include "bitmap_font.h"
#include "gl/viewport.h"
#include "gl/program.h"

namespace cgl
{
  class TextRenderer
  {
  public:
    TextRenderer();
    
    ~TextRenderer();
    
    std::string log() const;
    
    bool loadFont(std::string name,
                  const char* glyphFile,
                  const char* metricsFile);
    
    void setFont(std::string name);
    
    void begin(const Viewport& viewport);
    
    void end();
    
    void draw(const char* text, int x, int y);
    
  private:
    std::map<std::string, BitmapFont*> fonts_;
    std::vector<Texture*> textures_;
    BitmapFont* activeFont_;
    std::string errorLog_;
  };
}

#endif
