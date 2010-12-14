#ifndef __GRAY_PICTURE_H__
#define __GRAY_PICTURE_H__

#include "Picture.h"

class GrayPicture: public Picture {

	public: 

		GrayPicture(int width, int height);
		~GrayPicture();

		GrayPicture(unsigned char * data, int width, int height);
		GrayPicture(GrayPicture& pic);

		virtual Pixel getPixel(int x, int y);
		virtual void  setPixel(int x, int y, Pixel pix);
		virtual void  show();
        virtual Picture* clone();

		virtual unsigned char * getRawImage();
};

#endif
