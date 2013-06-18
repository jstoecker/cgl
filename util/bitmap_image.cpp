#include <fstream>
#include "bitmap_image.h"

using namespace cgl;

BitmapImage::BitmapImage() : width_(0), height_(0), data_(0)
{
}

BitmapImage::~BitmapImage()
{
  if (data_)
    delete[] data_;
}

unsigned BitmapImage::width() const
{
  return width_;
}

unsigned BitmapImage::height() const
{
  return height_;
}

const unsigned char* BitmapImage::data() const
{
  return data_;
}

std::string BitmapImage::log() const
{
  return log_;
}

bool BitmapImage::read(const char* fileName)
{
  using namespace std;

  // delete any previous data
  if (data_)
    delete[] data_;

  // open file
  ifstream fin(fileName, ios::in | ios::binary); 
  if (!fin) {
    log_ = "File not found: " + std::string(fileName);
    return false;
  }

  // read the byte offset for pixel data start
  fin.seekg(0x0A, ios::beg);
  unsigned short dataStart = 0;
  fin.read((char*)&dataStart, sizeof(unsigned char));

  // read the image dimensions
  fin.seekg(0x12, ios::beg);
  fin.read((char*)&width_, sizeof(unsigned int));
  fin.read((char*)&height_, sizeof(unsigned int));

  unsigned short planes = 0;
  fin.read((char*)&planes, sizeof(unsigned short));
  if (planes != 1) {
    log_ = "Number of color planes must be 1";
    return false;
  }

  unsigned short bpp = 0;
  fin.read((char*)&bpp, sizeof(unsigned short));
  if (bpp != 24) {
    log_ = "Image must be 24 bits per pixel (BGR format)";
    return false;
  }

  // read the pixel data
  unsigned size = width_ * height_ * 3;
  data_ = new unsigned char[size];
  fin.seekg(dataStart, ios::beg);
  fin.read((char*)data_, sizeof(unsigned char) * size);

  fin.close();
  log_ = "";
  return true; 
}
