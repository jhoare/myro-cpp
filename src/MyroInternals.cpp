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

CImg_display::CImg_display(myro_img& img, const char* window_name) 
: img(img),
  window_name(window_name), 
  img_changed(false),
  mx(-1),my(-1),clickedx(-1),clickedy(-1)
{}

CImg_display::CImg_display(myro_img* img, const char* window_name) 
: img(*img),
  window_name(window_name), 
  img_changed(false),
  mx(-1),my(-1),clickedx(-1),clickedy(-1)
{}

void CImg_display::run(){
    cil::CImgDisplay displaywin(img,window_name.c_str());
    mx = my = -1;

    while ( !stopRequested && !displaywin.is_closed()){
        displaywin.wait(50);
        {
            boost::mutex::scoped_lock l(img_mutex);
            if ( img_changed ){
                img_changed = false;
                displaywin.display(img);
            }
            mx = displaywin.mouse_x();
            my = displaywin.mouse_y();
            button = displaywin.button();
            // If its valid, send a wakeup to the mouse condition variable, if we're 
            if ( mx >= 0 && my >= 0 && button ){
                clickedx = mx;
                clickedy = my;
                mouse.notify_one();
            }
        }
    }
}

void CImg_display::change_image(myro_img& img){
    boost::mutex::scoped_lock l(img_mutex);
    this->img.assign(img);
    this->img_changed = true;
}

void CImg_display::change_image(myro_img* img){
    this->change_image(*img);
}

std::string CImg_display::getName(){
    return window_name;
}

Point CImg_display::getMouseClick(){
    boost::mutex::scoped_lock l(img_mutex);
    mouse.wait(img_mutex);
    return Point(clickedx,clickedy);
}

Point CImg_display::getLastClick(){
    boost::mutex::scoped_lock l(img_mutex);
    return Point(clickedx,clickedy);
}

Point CImg_display::getMouseCoords(int& button){
    boost::mutex::scoped_lock l(img_mutex);
    button = this->button;
    return Point(mx,my);
}


typedef std::map<std::string, CImg_display*> myro_cimg_display_map;
myro_cimg_display_map display_map;
boost::mutex map_mutex;

// Should already have mutex when calling me!
static inline void clean_dead_threads(){
    myro_cimg_display_map::iterator it;
    for (it = display_map.begin(); it != display_map.end();){
        CImg_display *t = it->second;
        if ( ! t->running() ){
            t->join();
            display_map.erase(it++);
        }
        else{
            it++;
        }
    }
}

CImg_display* set_picture_window(myro_img& img, const char* window_name){
    boost::mutex::scoped_lock l(map_mutex);
    clean_dead_threads();
    CImg_display* disp;
    myro_cimg_display_map::iterator it = display_map.find(window_name);
    if ( it == display_map.end() ){
        disp = new CImg_display(img, window_name);
        disp->start();
    }
    else{
        disp = it->second;
        display_map.erase(it);
        disp->change_image(img);
    }
    return disp;
}

void nonblock_display_window(CImg_display* thread){
    boost::mutex::scoped_lock l(map_mutex);
    clean_dead_threads();

    if ( display_map.find(thread->getName()) != display_map.end() ){
        // Shouldn't get here...
        std::cerr << "Error: trying to queue an image when one with the name is already queue!." << std::endl;
    }
    display_map[thread->getName()] = thread;
}
