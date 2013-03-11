#ifndef CGL_BITMAP_IMAGE_H_
#define CGL_BITMAP_IMAGE_H_

#include <string>

namespace cgl
{
  
  /// Loads and stores pixel values from a 24-bits-per-pixel BMP format image.
  class BitmapImage
  {
  public:
    BitmapImage();
    ~BitmapImage();
    
    /// Width of the image in pixels.
    unsigned width() const;
    
    /// Height of the image in pixels.
    unsigned height() const;
    
    /// Pixel values as unsigned bytes.
    const unsigned char* data() const;
    
    /// Returns error message if read() fails.
    std::string log() const;
    
    /// Reads a .bmp file into this class.
    bool read(const char* file_name);
    
  private:
    unsigned width_;
    unsigned height_;
    unsigned char* data_;
    std::string log_;
  };
  
}

#endif
