#ifndef __PICTURE_H__
#define __PICTURE_H__

#include<exception>
#include<string>

/**
 * A pixel structure that respesents a single pixel of an Image. 
 */
struct Pixel {
    int R;
    int G;
    int B;
};


/**
 * @class Picture
 *
 * The abstract Picture object that represents a picture taken from a robot. 
 *
 * @author Richard Edwards, John Hoare
 */
class Picture {
    public:
    /**
     * Exception that is thrown if the Picture is indexed out of Bounds
    class IndexOutOfBoundsException : public std::exception {
        public:
            IndexOutOfBoundsException(int width, int height, 
                                      int given_width, int given_height);
            ~IndexOutOfBoundsException() throw();
            virtual const char* what() throw();
        private: 
            std::string message;
    };
     */

    public:

        Picture(int width, int height);
        ~Picture();

        /**
         * @return A pixel struct representing the pixel at x,y
         */
        virtual Pixel getPixel(int x, int y)=0;
        /**
         * Set the value of a pixel at x,y to be the given pixel pix.
         */
        virtual void  setPixel(int x, int y, Pixel pix)=0;
        /**
         * Display the picture on the screen.
         */
        virtual void  show()=0;
        /**
         * Get a pointer to the underlying memory representing the 
         * image.
         */
        virtual unsigned char * getRawImage()=0;

        /** 
         * Get a "clone" of this picture. A clone is also a copy. 
         * If you'd like another copy of this picture use this function.
         *
         *
         * Example: 
         * Picture* pic = robot.takePicture("color");
         * Picture* pic2 = pic->clone();
         *
         * From this you'll have two "copies" of the same picture, so you're 
         * free to change around "pic" without worry of changing "pic2" 
         *
         * @return A clone of this picture
         */
        virtual Picture* clone() = 0;

        int getHeight();
        int getWidth();

        /**
         * Static method to print out an error message when a user has 
         * gone out of bounds. 
         */
        static void out_of_bounds_error(int width, int height, 
                            int given_width, int given_height);

    protected:

        unsigned char * image_data;
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
