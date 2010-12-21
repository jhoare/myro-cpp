#include "Filter.h"

Filter::Filter(int image_height, int image_width, int color_mode){
	imageHeight = image_height;
	imageWidth = image_width;
	colorMode = color_mode;
}

Filter::~Filter() {
}

void Filter::applyFilter(Picture * image) {
	this->filter(image);
}

void Filter::filter(Picture* image) {
	return;
}

int Filter::getHeight() {
	return imageHeight;
}

int Filter::getWidth() {
	return imageWidth;
}

int Filter::getColorMode() {
	return colorMode;
}
