#include "ColorPicture.h"
#include <jpeglib.h>
#include <cstdio>
/*
#include <FL/Fl.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
*/
#include "MyroInternals.h"

using namespace std;

ColorPicture::ColorPicture(): Picture() {};

ColorPicture::ColorPicture(unsigned char * data, int width, int height)
    : Picture(width, height), image_data(width,height,1,3){
  
    loadInterlacedImage(data);
    this->width = width;
    this->height = height;
}

ColorPicture::ColorPicture(int width, int height): 
    Picture(width, height), image_data(width,height,1,3,0)
{
    this->width = width;
    this->height = height;
}

ColorPicture::ColorPicture(ColorPicture& pic):
    Picture(pic.width, pic.height), image_data(pic.image_data){
}

Pixel ColorPicture::getPixel(int x, int y) {
    if ( x >= width || y >= height )
        Picture::out_of_bounds_error(width,height,x,y);
    Pixel result;
    result.R = image_data(x,y,0,0);
    result.G = image_data(x,y,0,1);
    result.B = image_data(x,y,0,2);
    return result;
}

void ColorPicture::setPixel(int x, int y, Pixel pix) {
    if ( x >= width || y >= height )
        Picture::out_of_bounds_error(width,height,x,y);
    image_data(x,y,0,0) = pix.R;  
    image_data(x,y,0,1) = pix.G;    
    image_data(x,y,0,2) = pix.B;    
}

void ColorPicture::show() {
    CImg_display* disp = new CImg_display(image_data, "Color Picture");
    disp->start();
    disp->join();
    delete disp;
}

Picture* ColorPicture::clone(){
    Picture* newpic = new ColorPicture(*this);
    return newpic;
}

bool ColorPicture::loadPicture(const char* filename){
  /* And we're done! */
  return true;
}

void ColorPicture::savePicture(const char* filename){
  /* And we're done! */
}

myro_img& ColorPicture::getRawImage(){
    return image_data;
}

void ColorPicture::loadInterlacedImage(unsigned char* img){
    cimg_forXY(image_data,x,y){
        image_data(x,y,0,0) = img[y*width*3+x*3];
        image_data(x,y,0,1) = img[y*width*3+x*3+1];
        image_data(x,y,0,2) = img[y*width*3+x*3+2];
    }
}
