#include "MyroInternals.h"
#include <iostream>

//------------------------------
// Threaded
//------------------------------

Threaded::Threaded() : stopRequested(false), _running(false), runThread(NULL) {};

Threaded::~Threaded(){
    if ( this->running() )
        this->stop();
    if ( runThread )
        delete runThread;
}

void Threaded::start() {
    assert(!runThread);
    stopRequested = false;
    boost::mutex::scoped_lock l(startup_mutex);
    runThread = new boost::thread(boost::bind(&Threaded::startRun, this));
    startup_condition.wait(l);
}
void Threaded::stop() {
    assert(runThread);
    stopRequested = true;
    this->join();
}
void Threaded::join() { 
    if ( runThread ){
        runThread->join(); 
        delete runThread;
        runThread = NULL;
    }
}

bool Threaded::running(){
    boost::mutex::scoped_lock l(startup_mutex);
    return _running;
}

void Threaded::startRun(){
    {
        // Hey I'm the new thread, and I've started running!
        boost::mutex::scoped_lock l(startup_mutex);
        _running = true;
        startup_condition.notify_one();
    }
    this->run();
    {
        boost::mutex::scoped_lock l(startup_mutex);
        _running = false;
    }
}

CImg_display::CImg_display(myro_img& img, const char* window_name) : img(img), window_name(window_name){
}

void CImg_display::run(){
    cil::CImgDisplay displaywin(img,window_name.c_str());

    while ( !stopRequested && !displaywin.is_closed()){
        displaywin.wait(1000);
    }
}
