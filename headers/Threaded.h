#pragma once
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <boost/shared_ptr.hpp>

/// Inherit from this to get threading.  The usage is:
///     threaded.start()
///     threaded.join()
/// Implement the run() function as the thread.
class Threaded {
    public:
        Threaded() : stopRequested(false), runThread() {}
        virtual void start() {
            assert(!runThread);
            runThread = boost::shared_ptr<boost::thread>
                (new boost::thread
                 (boost::bind(&Threaded::run, this)));
        }
        virtual void stop() {
            assert(runThread);
            stopRequested = true;
            runThread->join();
        }
        void join() { 
            runThread->join(); 
        }
    protected:
        volatile bool stopRequested;
    private:
        virtual void run() = 0;
        boost::shared_ptr<boost::thread> runThread; 
};
