#include "MyroInternals.h"
#include <iostream>

//------------------------------
// Threaded
//------------------------------

Threaded::Threaded() : stopRequested(false), _running(false), runThread() {};

Threaded::~Threaded(){
    if ( this->running() )
        this->stop();
}

void Threaded::start() {
    assert(!runThread);
    stopRequested = false;
    boost::mutex::scoped_lock l(startup_mutex);
    runThread = boost::shared_ptr<boost::thread>
        (new boost::thread
         (boost::bind(&Threaded::startRun, this)));
    startup_condition.wait(l);
}
void Threaded::stop() {
    assert(runThread);
    stopRequested = true;
    runThread->join();
}
void Threaded::join() { 
    runThread->join(); 
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

//------------------------------
// FLTKThread
//------------------------------

FLTKThread::FLTKThread(){};
FLTKThread::~FLTKThread(){
    if ( this->running() )
        this->stop();
}

void FLTKThread::run(){
    while (!stopRequested){
        //std::cerr << "FLTKThread::run()" << std::endl;
        /*
        {
            boost::mutex::scoped_lock l(vector_lock);
            for (unsigned int i=0; i<to_notify.size(); i++){
                if ( to_notify[i]->win->shown() ){
                    boost::mutex::scoped_lock j(to_notify[i]->m);
                    to_notify[i]->cond.notify_one();
                }
            }
        }
        */
        {
            boost::mutex::scoped_lock l(window_lock);
            for(unsigned int i=0; i<windows.size(); i++){
                if(windows[i]->visible()){
                    if (!Fl::check()) {
                        // Do something...
                    }
                }else if ( !Fl::wait() ){
                    // Do something...
                }
                windows[i]->refresh();
            }
        }
        Fl::wait(0.05);
        usleep(50000);
    }
}

//------------------------------
// FLTKManager
//------------------------------
FLTKThread FLTKManager::thread;

void FLTKManager::block_until_closed(Fl_Window* win){
    if (!thread.running()) thread.start();
    //std::cerr << "FLTKManager::block_until_closed(): Blocking" << std::endl;
    //fltknotify *notify = new fltknotify;
    //notify->win = win;
    boost::mutex m;
    boost::condition cond;
    ((ImageWindow*)win)->NotifyWhenClosed(&m,(void*)&cond);
    /*
    {
        boost::mutex::scoped_lock l(thread.vector_lock);
        thread.to_notify.push_back(notify);
    }
    */
    boost::mutex::scoped_lock l(m);
    cond.wait(m);
    //std::cerr << "FLTKManager::block_until_closed(): Closed!" << std::endl;
}

ImageWindow* FLTKManager::get_image_window(int width, int height, char * title){
    return get_image_window(0,0,width,height,title);
}

ImageWindow* FLTKManager::get_image_window(int x, int y, int width, int height, char* title){
    if (!thread.running()) thread.start();
    ImageWindow* ret = new ImageWindow(x,y,width,height,title);
    {
        boost::mutex::scoped_lock l(thread.window_lock);
        ret->show();
        thread.windows.push_back(ret);
    }
    return ret;
}

bool FLTKManager::remove_image_window(ImageWindow* win){
    boost::mutex::scoped_lock l(thread.window_lock);
    std::vector<ImageWindow*>::iterator it;
    for (it = thread.windows.begin(); it != thread.windows.end(); it++){
        if (*it == win){
            thread.windows.erase(it);
            return true;
        }
    }
    return false;
}
