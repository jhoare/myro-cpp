#define cimg_use_jpeg
#include "GrayPicture.h"
#include <cstdio>
#include "MyroInternals.h"

using namespace std;

GrayPicture::GrayPicture() : Picture() {};

GrayPicture::GrayPicture(int width, int height) 
:Picture(width, height), image_data(width,height,1,1,0) {

    this->width = width;
    this->height = height;
}

GrayPicture::GrayPicture(unsigned char * data, int width, int height)
:Picture(width, height), image_data(data,width,height,1,1) {
    this->width = width;
    this->height = height;
}

GrayPicture::GrayPicture(GrayPicture& pic)
:Picture(pic.width, pic.height),image_data(pic.image_data){

    this->width = pic.width;
    this->height = pic.height;

    image_data = pic.image_data;
}

Pixel GrayPicture::getPixel(int x, int y) {
    if ( x >= width || y >= height )
        Picture::out_of_bounds_error(width,height,x,y);
    Pixel result;
    result.R = image_data(x,y,0,0);
    result.G = result.R;
    result.B = result.R;
    return result;
}

void GrayPicture::setPixel(int x, int y, Pixel pix) {
    if ( x >= width || y >= height )
        Picture::out_of_bounds_error(width,height,x,y);
    image_data(x,y,0,0) = pix.R;
}

Picture* GrayPicture::clone(){
    Picture* newpic = new GrayPicture(*this);
    return newpic;
}

void GrayPicture::show() {
    CImg_display* disp = new CImg_display(image_data, "Gray Picture");
    disp->start();
    disp->join();
    delete disp;
}

myro_img& GrayPicture::getRawImage(){
    return image_data;
}

bool GrayPicture::loadPicture(const char* filename){
  image_data.load_jpeg(filename);
  /* And we're done! */
  return true;
}

void GrayPicture::savePicture(const char* filename){
  image_data.save_jpeg(filename);
  /* And we're done! */
}
