#include "Picture.h"

Picture::Picture(int width, int height) {
	this->width =  width;
	this->height = height;
}

Picture::~Picture() {
	//nothing to be done for now
}

int Picture::getHeight() {
	return height;
}

int Picture::getWidth() {
	return width;
}

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
// END C-style Wrappers for the objects...
