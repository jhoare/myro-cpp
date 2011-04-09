#ifndef __MYRO_CIMG_H
#define __MYRO_CIMG_H
#include <cstdio>
#include <jpeglib.h>
#include <jerror.h>


// So the CImg Library wants you to #define certian things to "enable" or "diable" 
// functionality.
#define cimg_use_jpeg

// Use the jpeg_buffer to decompress a jpeg image from memory (instead of from file)
#define cimg_plugin "CImg/jpeg_buffer.h"
#include <CImg/CImg.h>


namespace cil = cimg_library;
typedef cil::CImg<unsigned char> myro_img;
#endif
