#ifndef __IMAGE_WINDOW_H__
#define __IMAGE_WINDOW_H__

#include <Fl/Fl_Window.H>
#include <Fl/Fl_Image.H>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>

//class Fl_Thread; // Forward Declaration

class ImageWindow : public Fl_Window {

	public:
		ImageWindow(int width, int height, char * title);
		ImageWindow(int x, int y, int width, int height, char * title);
                ~ImageWindow();
		void set_color_mode(int color_mode);
		void loadImageSource(unsigned char * data, int width, int height);
		virtual void draw();
        virtual int handle(int event);
        void NotifyWhenClosed(boost::mutex * mutex, boost::condition* cond);
        void refresh();

	private:

		Fl_RGB_Image* image;
		int color_mode;
        boost::mutex exclusive;

        // Mutex and Condition variables to notify when I am closed.
        boost::mutex* m;
        boost::condition* cond;
        //Fl_Thread *fl_thread;
};

#endif
