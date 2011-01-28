#pragma once
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <boost/shared_ptr.hpp>
#include <Fl/Fl.H>
#include <vector>
#include "ImageWindow.h"

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
        boost::shared_ptr<boost::thread> runThread; 
        boost::mutex startup_mutex;
        boost::condition startup_condition;
};


struct fltknotify{
    boost::mutex m;
    boost::condition cond;
    Fl_Window *win;
};



class FLTKThread : public Threaded{
    private:
    boost::mutex vector_lock;
    std::vector<fltknotify*> to_notify;
    boost::mutex window_lock;
    std::vector<ImageWindow*> windows;

    public:
    FLTKThread();
    ~FLTKThread();
    void run();

    friend class FLTKManager;
};

/// A singleton class, with static methods 
class FLTKManager{
    static FLTKThread thread;
    public:
    static void block_until_closed(Fl_Window* win);
    static ImageWindow* get_image_window(int width, int height, char* title);
    static ImageWindow* get_image_window(int x, int y, int width, int height, 
                                                                  char* title);
    static bool remove_image_window(ImageWindow* win);
};

