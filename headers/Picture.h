#ifndef __PICTURE_H__
#define __PICTURE_H__

typedef struct Pixel_t {
	int R;
	int G;
	int B;
} Pixel;

class Picture {

	public:

		Picture(int width, int height);
		~Picture();

		virtual Pixel getPixel(int x, int y)=0;
		virtual void  setPixel(int x, int y, Pixel pix)=0;
		virtual void  show()=0;
		virtual unsigned char * getRawImage()=0;

		int getHeight();
		int getWidth();

	private:

		int width;
		int height;


};
// functions added for lab 6 by Nick
int getWidth(Picture *p);
int getHeight(Picture *p);
void show(Picture *p);
Pixel getPixel(Picture *p, int x, int y);
int getPixelValue_grey(Picture *p, int x, int y);
void setPixelColor(Picture *p, int x, int y, int R, int G, int B);

#endif
