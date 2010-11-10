#include "ImageWindow.h"
#include "MyroInternals.h"
#include <FL/Fl.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include <iostream>
#include <cstring>

class Fl_Thread : public Threaded{
    public:
        Fl_Thread(ImageWindow * window);
        //boost::mutex& setup, boost::condition& setup_notify);
        //void start();
        virtual void run();
        //void stop();
    private:
        //Fl_Window * window;
        ImageWindow * window;
        //boost::mutex& setup;
        //boost::condition& setup_notify;
};

ImageWindow::ImageWindow(int width, int height, char * title) 
: Fl_Window(width, height, title), 
    image(NULL)//,
    //fl_thread(new Fl_Thread(this))
{ 
    // Start the Fl_Thread display thread.
    //fl_thread->start();
}


ImageWindow::ImageWindow(int x, int y, int width,
        int height, char * title)
: Fl_Window(x, y, width, height, title) {
    unsigned char temp[width*height*3];
    std::memset(temp,255,width*height*3);
    image = new Fl_RGB_Image(temp,width,height);
}

ImageWindow::~ImageWindow(){
    // Close and clean up our display thread
    //fl_thread->stop();
    //delete fl_thread;
    if (image) delete image;
}

void ImageWindow::loadImageSource(unsigned char * data, int width, int height) {
    boost::mutex::scoped_lock l(exclusive);
    if(image)
        delete image;
    image = new Fl_RGB_Image((const unsigned char*)data, width, height);

}

void ImageWindow::set_color_mode(int color_mode) {
    this->color_mode = color_mode;
}

void ImageWindow::draw() {
    if(image != NULL) {
        if(color_mode)
            fl_draw_image((unsigned char*)(*(image->data())), 0, 0, image->w(),
                    image->h());
        else
            fl_draw_image((unsigned char*)(*(image->data())), 0, 0, image->w(),
                    image->h(), 1);
    }
}

void ImageWindow::refresh() {
    boost::mutex::scoped_lock l(exclusive);
    this->redraw();
}

Fl_Thread::Fl_Thread(ImageWindow* window) : Threaded(), window(window)
{}

// FL Thread
void Fl_Thread::run(){
    {
        //boost::mutex::scoped_lock l(setup);
        this->window->show();
        //std::cerr << "Fl_Thread::run() - started" << std::endl;
        //setup_notify.notify_one();
    }

    while(!this->stopRequested){
        //std::cerr << "Fl_Thread::run()" << std::endl;
        if( this->window->visible() ) {
            if(!Fl::check())
                break;
        }
        else if( !Fl::wait() )
            break;
        //printf("start_stream() : imageWindow->redraw()\n");
        //this->imageWindow->redraw();
        this->window->refresh();
        usleep(50000); // Sleep for .05 seconds, giving a 20hz refresh rate
        //boost::thread::yield();
    }
    this->window->hide();
    //this->imageWindow->hide();

    //std::cerr << "Fl_Thread::run() - ending" << std::endl;

    return;
}
