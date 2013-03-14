#include "text_renderer.h"
#include <fstream>

using namespace cgl;

TextRenderer::TextRenderer()
{
  activeFont_ = NULL;
}

TextRenderer::~TextRenderer()
{
  if (!textures_.empty()) {
    for (unsigned i = 0; i < textures_.size(); ++i) {
      textures_[i]->glDelete();
      delete textures_[i];
    }
  }
  
  if (!fonts_.empty()) {
    for (std::map<std::string, BitmapFont*>::iterator it = fonts_.begin();
         it != fonts_.end();
         ++it)
    {
      delete it->second;
    }
  }
}

std::string TextRenderer::log() const
{
  return errorLog_;
}

bool TextRenderer::loadFont(std::string name,
                            const char* glyphFile,
                            const char* metricsFile)
{
  BitmapImage bmp;
  if (!bmp.read(glyphFile)) {
    errorLog_ = bmp.log();
    return false;
  }
  
  // pre-multiply alpha
  long pixelin = 0;
  long pixelout = 0;
  unsigned char* buf = new unsigned char[bmp.width() * bmp.height() * 4];
  for (unsigned i = 0; i < bmp.width() * bmp.height(); ++i) {
    unsigned char red = bmp.data()[pixelin++];
    unsigned char green = bmp.data()[pixelin++];
    unsigned char blue = bmp.data()[pixelin++];
    unsigned char alpha = red;
    float falpha = alpha / 255.f;
    buf[pixelout++] = red * falpha;
    buf[pixelout++] = green * falpha;
    buf[pixelout++] = blue * falpha;
    buf[pixelout++] = alpha;
  }
  
  unsigned char glyphWidths[256];
  std::ifstream mfile(metricsFile, std::ios::in | std::ios::binary);
  if (!metricsFile) {
    errorLog_ = "Font metrics file not found: " + std::string(metricsFile);
    return false;
  }
  mfile.read((char*)glyphWidths, sizeof(unsigned char)*256);
  mfile.close();
  
  Texture* fontTexture = new Texture;
  fontTexture->generate(GL_TEXTURE_2D);
  fontTexture->bind();
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  fontTexture->setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  fontTexture->setParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  fontTexture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  fontTexture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  fontTexture->setData2D(0, GL_RGBA, bmp.width(), bmp.height(), GL_RGBA,
                        GL_UNSIGNED_BYTE, buf);

  delete[] buf;
  
  textures_.push_back(fontTexture);
  BitmapFont* font = new BitmapFont(*fontTexture, glyphWidths);
  fonts_[name] = font;
  
  if (!activeFont_)
    activeFont_ = font;
  
  return true;
}

void TextRenderer::setFont(std::string name)
{
  activeFont_ = fonts_[name];
}

void TextRenderer::begin(const Viewport& viewport)
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  activeFont_->begin(viewport);
}

void TextRenderer::end()
{
  activeFont_->end();
  glDisable(GL_BLEND);
}

void TextRenderer::draw(const char* text, int x, int y)
{
  activeFont_->drawString(text, x, y);
}
