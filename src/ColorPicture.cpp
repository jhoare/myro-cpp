#include "ColorPicture.h"
#include "ImageWindow.h"
/*
#include <FL/Fl.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
*/
#include "MyroInternals.h"

ColorPicture::ColorPicture(unsigned char * data, int width, int height)
	: Picture(width, height) {

	image_data = new unsigned char[width * height * 3];
	for(int i = 0; i < width * height * 3; i++)
		image_data[i] = data[i];

	this->width = width;
	this->height = height;
}

ColorPicture::ColorPicture(int width, int height): 
	Picture(width, height) {

	this->width = width;
	this->height = height;

	image_data = new unsigned char[width * height * 3];
	for(int i = 0; i < width * height * 3; i++) {
		image_data[i] = 0;
	}
}

ColorPicture::ColorPicture(ColorPicture& pic):
	Picture(pic.width, pic.height) {	
	image_data = new unsigned char[pic.width * pic.height * 3];
	for(int i = 0; i < pic.width * pic.height * 3; i++)
		image_data[i] = pic.image_data[i];
}

Pixel ColorPicture::getPixel(int x, int y) {
    if ( x >= width || y >= height )
        Picture::out_of_bounds_error(width,height,x,y);
	Pixel result;
	result.R = image_data[(y * width * 3) + (x * 3)];
	result.G = image_data[(y * width * 3) + (x * 3)+1];
	result.B = image_data[(y * width * 3) + (x * 3)+2];
	return result;
}

void ColorPicture::setPixel(int x, int y, Pixel pix) {
    if ( x >= width || y >= height )
        Picture::out_of_bounds_error(width,height,x,y);
	image_data[(y * width * 3) + (x * 3)] = pix.R;	
	image_data[(y * width * 3) + (x * 3)+1] = pix.G;	
	image_data[(y * width * 3) + (x * 3)+2] = pix.B;	
}

void ColorPicture::show() {
    ImageWindow * win = FLTKManager::get_image_window(width,height,
                                                               "Color Picture");
    win->set_color_mode(1);
    win->loadImageSource(image_data, width, height);

    FLTKManager::block_until_closed(win);
}

Picture* ColorPicture::clone(){
    Picture* newpic = new ColorPicture(width,height);
    for(int x = 0; x < width; x++)
        for(int y = 0; y < height; y++)
            newpic->setPixel(x,y,this->getPixel(x,y));
    return newpic;
}

unsigned char * ColorPicture::getRawImage() {
	return image_data;
}
