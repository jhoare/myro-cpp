#include "GrayPicture.h"
#include "MyroInternals.h"

GrayPicture::GrayPicture(int width, int height) 
	:Picture(width, height) {
	
	image_data = new unsigned char[width * height];
	for(int i = 0; i < width * height; i++)
		image_data = 0;

	this->width = width;
	this->height = height;
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
    if ( x >= width || y >= height )
        Picture::out_of_bounds_error(width,height,x,y);
	Pixel result;
	result.R = image_data[(y * width) + x];
	result.G = result.R;
	result.B = result.R;
	return result;
}

void GrayPicture::setPixel(int x, int y, Pixel pix) {
    if ( x >= width || y >= height )
        Picture::out_of_bounds_error(width,height,x,y);
	image_data[(y * width) + x] = pix.R;
}

unsigned char * GrayPicture::getRawImage() {
	return image_data;
}

Picture* GrayPicture::clone(){
    Picture* newpic = new GrayPicture(width,height);
    for(int x = 0; x < width; x++)
        for(int y = 0; y < height; y++)
            newpic->setPixel(x,y,this->getPixel(x,y));
    return newpic;
}

void GrayPicture::show() {
    ImageWindow * win = FLTKManager::get_image_window(width,height,
                                                               "Gray Picture");
    win->set_color_mode(0);
    win->loadImageSource(image_data, width, height);

    FLTKManager::block_until_closed(win);
}
