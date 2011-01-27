#ifndef __GRAY_PICTURE_H__
#define __GRAY_PICTURE_H__

#include <Picture.h>

/** @addtogroup picture
 * @{
 */

/// Object Representing a Gray Picture 
class GrayPicture: public Picture {

    public: 

        GrayPicture();
        GrayPicture(int width, int height);
        ~GrayPicture();

        GrayPicture(unsigned char * data, int width, int height);
        GrayPicture(GrayPicture& pic);

        virtual Pixel getPixel(int x, int y);
        virtual void  setPixel(int x, int y, Pixel pix);
        virtual void  show();
        virtual Picture* clone();
        virtual bool loadPicture(const char* filename);
        virtual void savePicture(const char* filename);

};

///@}

#endif
