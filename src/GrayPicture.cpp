#include "GrayPicture.h"
#include "MyroInternals.h"
//#include <Magick++.h>
//using namespace Magick;

GrayPicture::GrayPicture(int width, int height) 
	:Picture(width, height) {
	
	image_data = new unsigned char[width * height];
	for(int i = 0; i < width * height; i++)
		image_data = 0;

	this->width = width;
	this->height = height;
}

GrayPicture::~GrayPicture() {
	delete image_data;
}

GrayPicture::GrayPicture(unsigned char * data, int width, int height)
	:Picture(width, height) {
	
	image_data = new unsigned char[width * height];
	for(int i = 0; i < width * height; i++)
		image_data[i] = data[i];

	this->width = width;
	this->height = height;
}

GrayPicture::GrayPicture(GrayPicture& pic)
	:Picture(pic.width, pic.height) {
	
	this->width = pic.width;
	this->height = pic.height;

	image_data = new unsigned char[pic.width * pic.height];

	for(int i = 0; i < pic.width * pic.height; i++)
		image_data[i] = pic.image_data[i];
}

Pixel GrayPicture::getPixel(int x, int y) {
	Pixel result;
	result.R = image_data[(y * width) + x];
	result.G = result.R;
	result.B = result.R;
	return result;
}

void GrayPicture::setPixel(int x, int y, Pixel pix) {
	image_data[(y * width) + x] = pix.R;
}

unsigned char * GrayPicture::getRawImage() {
	return image_data;
}

void GrayPicture::show() {
    ImageWindow * win = FLTKManager::get_image_window(width,height,
                                                               "Gray Picture");
    win->set_color_mode(0);
    win->loadImageSource(image_data, width, height);

    FLTKManager::block_until_closed(win);
}
