#pragma once
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
//#include <boost/shared_ptr.hpp>
#include <vector>
#include <MyroCImg.h>

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
        virtual void run();
    private:
        myro_img& img;
        std::string window_name;
};
