#ifndef __COLOR_PICTURE_H__
#define __COLOR_PICTURE_H__

#include "Picture.h"

class ColorPicture: public Picture {

	public: 
		//functions for students to use, if they need to create a picture.
		ColorPicture(int width, int height);
		ColorPicture(ColorPicture& pic);

		//functions for scribbler code to use
		ColorPicture(unsigned char * data, int width, int height);
		~ColorPicture();

		virtual Pixel getPixel(int x, int y);
		virtual void setPixel(int x, int y, Pixel pix);
		virtual void show();

		virtual unsigned char * getRawImage();

	private:

		unsigned char * image_data;
		int width;
		int height;

	
};

#endif
