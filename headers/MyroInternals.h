#pragma once
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
//#include <boost/shared_ptr.hpp>
#include <vector>
#include <MyroCImg.h>
#include <Graphics.h>

// Inherit from this to get threading.  The usage is:
//     threaded.start()
//     threaded.join()
// Implement the run() function as the thread.
class Threaded {
    public:
        Threaded();
        ~Threaded();
        virtual void start();
        virtual void stop();
        void join();
        bool running();
    protected:
        volatile bool stopRequested;
    private:
        void startRun();
        virtual void run() = 0;
        volatile bool _running;
        boost::thread * runThread;
        //boost::shared_ptr<boost::thread> runThread; 
        boost::mutex startup_mutex;
        boost::condition startup_condition;
};

class CImg_display : public Threaded {
    public:
        CImg_display(myro_img& img, const char* window_name);
        CImg_display(myro_img* img, const char* window_name);
        virtual void run();
        void change_image(myro_img* img);
        void change_image(myro_img& img);
        Point getMouseClick();
        Point getLastClick();
        Point getMouseCoords(int& buttons);
        std::string getName();
    private:
        std::list<GraphicsObject*> draw_commands;
        myro_img img;
        std::string window_name;
        boost::mutex img_mutex;
        boost::condition mouse;
        bool img_changed;
        int mx;
        int my;
        int clickedx;
        int clickedy;
        int button;
};


// This is a factory function that will return a pointer to the Display thread, so the caller can 
// then block on it if they so choose.
CImg_display * set_picture_window(myro_img& img, const char* window_name);

// This is a funciton that has its own thread behind it to join() any display window threads that 
// exit, to avoid a memory leak. 
void nonblock_display_window(CImg_display* thread);
