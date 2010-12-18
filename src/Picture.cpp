#include "Picture.h"
#include "ColorPicture.h"
#include "GrayPicture.h"
#include <iostream>
#include <sstream>
#include <cstdlib>

Picture::Picture(){
    this->width = this->height = 0;
}

Picture::Picture(int width, int height) {
    this->width =  width;
    this->height = height;
}

Picture::~Picture() {
    delete image_data;
}

int Picture::getHeight() {
    return height;
}

int Picture::getWidth() {
    return width;
}

unsigned char* Picture::getRawImage(){
    return image_data;
}

void Picture::out_of_bounds_error(int width, int height, int given_width, 
                                                    int given_height){
    std::cerr << std::endl << "ERROR: Accessing Image Out of bounds." 
        << std::endl
       << "  Image Width:  " <<  width << std::endl
       << "  Image Height: " << height << std::endl
       << "  Attempted access to Pixel at (" << given_width << "," 
                        << given_height << ")" << std::endl;
    exit(1);
}

/*
Picture::IndexOutOfBoundsException::IndexOutOfBoundsException(int width, 
                                int height, int given_width, int given_height)
{
    std::stringstream ss;
    ss << "Accessing Image Out of bounds." << std::endl
       << "  Image Width:  " <<  width << std::endl
       << "  Image Height: " << height << std::endl
       << "  Attempted access to Pixel at (" << given_width << "," 
                        << given_height << ")" << std::endl;
    message = ss.str();
    //std::cerr << message << std::endl;
}

Picture::IndexOutOfBoundsException::~IndexOutOfBoundsException() throw(){
}

const char* Picture::IndexOutOfBoundsException::what() throw(){
    //std::cerr << message << std::endl;
    return message.c_str();
}
*/

// Below are the C-style Wrappers for the objects...
int getWidth(Picture *p)
{
        return p->getWidth();
}

int getHeight(Picture *p)
{
        return p->getHeight();
}

void show(Picture *p)
{
        p->show();
}

Pixel getPixel(Picture *p, int x, int y)
{
        return p->getPixel(x, y);
}

int getPixelValue_grey(Picture *p, int x, int y)
{
        Pixel P=p->getPixel(x,y);
        return P.R;
}

void setPixelColor(Picture *p, int x, int y, int R, int G, int B)
{
        Pixel P=p->getPixel(x,y);
        P.R=R;
        P.G=G;
        P.B=B;
        p->setPixel(x, y, P);
}

Picture* loadPicture(const char* filename){
    Picture* ret = new ColorPicture();
    if ( ret->loadPicture(filename) )
        return ret;
    delete ret;
    ret = new GrayPicture();
    if ( ret->loadPicture(filename) )
        return ret;
    
    return NULL;
}

void loadPicture(Picture * p, const char* filename){
    p->loadPicture(filename);
}
void savePicture(Picture * p, const char* filename){
    p->savePicture(filename);
}

Picture* clone(Picture* p){
    return p->clone();
}
// END C-style Wrappers for the objects...
