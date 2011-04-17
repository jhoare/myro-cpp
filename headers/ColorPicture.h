#ifndef __COLOR_PICTURE_H__
#define __COLOR_PICTURE_H__

#include <Picture.h>

/** @addtogroup picture
 * @{
 */

/// Object Representing a Color Picture (also used for Blob Pictures)
class ColorPicture: public Picture {

    public: 
        //functions for students to use, if they need to create a picture.
        ColorPicture();
        ColorPicture(int width, int height);
        ColorPicture(ColorPicture& pic);

        //functions for scribbler code to use
        ColorPicture(unsigned char * data, int width, int height);
        ~ColorPicture();

        virtual Pixel getPixel(int x, int y);
        virtual void setPixel(int x, int y, Pixel pix);
        virtual void show(std::string windowname);
        virtual void show();
        virtual Picture* clone();
        virtual bool loadPicture(const char* filename);
        virtual void savePicture(const char* filename);
        virtual myro_img& getRawImage();
    private:
        void loadInterlacedImage(unsigned char* img);
        myro_img image_data;
};


///@}

#endif
