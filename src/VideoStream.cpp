#include "VideoStream.h"
#include "ImageWindow.h"
#include <assert.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <FL/Fl.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include <iostream>
#include <exception>
#include "MyroInternals.h"

#define image_height 192
#define image_width 256
#define RGB 3
static const int BUFFER_SIZE = 512;

class DisplayThread : public Threaded{
    public:
    DisplayThread(ImageWindow* imageWindow, circbuf* cb,
                          std::vector<Filter*>* filters,
                              boost::mutex& _filterLock);
    //virtual void start();
    virtual void run();
    //void stop();
    private:
    ImageWindow * imageWindow;
    circbuf* cb;
    std::vector<Filter*>* filters;
    boost::mutex& filterLock;
};

class CaptureThread : public Threaded{
    public:
    CaptureThread(Scribbler* robot, circbuf* cb, int color_mode);
    //void start();
    virtual void run();
    private:
    Scribbler* robot;
    circbuf* cb;
    int color_mode;
};

class circbuf{
    public:
        circbuf(int size){
            this->buf = new unsigned char*[size];
            this->size = size;
            this->start = this->end = 0;
        }
        ~circbuf(){
            delete buf;
        }
        void push(unsigned char* item){
            //std::cerr << "push()" << std::endl;
            boost::mutex::scoped_lock l(_lock);
            buf[end] = item;
            end = (end+1)%size;
            cv.notify_one();
            if ( end == start ){
                // We're overwriting old data.
                //start = (start+1)%size;
                // TODO: Handle this Better
                throw new std::exception;
            }
        }
        unsigned char* pop(){
            unsigned char* val;
            //std::cerr << "pop()" << std::endl;
            if ( start == end ){
                boost::mutex::scoped_lock l(_lock);
                while ( start == end ){
                    // We need to block and wait for something.
                    //std::cerr << "waiting up" << std::endl;
                    cv.wait(l);
                    //std::cerr << "waking up" << std::endl;
                }
            }
            val = buf[start]; 
            start = (start+1)%size;
            return val;
        }
        bool isEmpty(){
            return start == end;
        }
    private:
        unsigned char** buf;
        unsigned int size;
        unsigned int start;
        unsigned int end;
        boost::mutex _lock;
        boost::condition cv;
};

VideoStream::VideoStream(Scribbler * scrib, int color_mode) {
    this->myScrib = scrib;
    this->color_mode = color_mode;
    this->filters = new std::vector<Filter*>();
    this->running = false;
    this->id = -1;
}

VideoStream::~VideoStream() {
    this->endStream();
    filters->clear();
    delete filters;
}


// Dispaly/Update Thread
DisplayThread::DisplayThread(ImageWindow* imageWindow, circbuf* cb,
                                      std::vector<Filter*>* filters,
                                          boost::mutex& _filterLock)
:  Threaded(), filterLock(_filterLock)
{
    this->imageWindow = imageWindow;
    this->cb = cb;
    this->filters = filters;
}

void DisplayThread::run() {
    unsigned char* img_cur=NULL;
    unsigned char* img_new=NULL;

    while(!this->stopRequested){
        //std::cerr << "DisplayThread::run()" << std::endl;
        //printf("display_stream() Waiting on Picture\n");
        img_new = cb->pop();

        if ( this->stopRequested ) break;

        //printf("display_stream() Picture Received\n");

        {
            boost::mutex::scoped_lock l(filterLock);
            for(unsigned int i = 0; i < this->filters->size(); i++) {
                this->filters->at(i)->applyFilter(img_new);
            }
        }

        imageWindow->loadImageSource(img_new, image_width, image_height);

        if ( img_cur != NULL ){
            free(img_cur);
        }
        img_cur = img_new;

        imageWindow->refresh();

        //boost::thread::yield();
        usleep(1000); //hack to slow down the capture thread
                      //so that the other threads are scheduled
        //printf("display_stream() Image Updated\n");

    }
    return;
}


CaptureThread::CaptureThread(Scribbler* robot, circbuf* buf, int color_mode)
:Threaded()
{
    this->robot = robot;
    this->cb = buf;
    this->color_mode = color_mode;
}

void CaptureThread::run(){
    unsigned char * tempImageBuffer; 

    while(!this->stopRequested){
        //std::cerr << "CaptureThread::run()" << std::endl;
        //pthread_mutex_lock(videoData->refresh_lock);    

        //fprintf(stderr, "capture_image() Capturing Image\n");

        switch(this->color_mode) {
            case 0: tempImageBuffer
                        = robot->takePicture("grayjpeg")->getRawImage();
                break;
            case 1:
                    tempImageBuffer
                        = robot->takePicture("jpeg")->getRawImage();
                break;
            case 2:
                    tempImageBuffer
                        = robot->takePicture("blob")->getRawImage();
                break;
            default: 
            {
                throw "Invalid Color Mode\n";
            }
        }

        //printf("capture_image(): Image Loaded into Memory\n"); 
        cb->push(tempImageBuffer);
        usleep(1000); //hack to slow down the capture thread
                      //so that the other threads are scheduled
        //boost::thread::yield();
    }
    return;
}

void VideoStream::startStream() {
    if ( !running ){
        // This lock/condition variable combo is addressing an issue that 
        // shows up in cygwin where the fl_window thread doesn't get run
        // sometimes, depending on what happens immediately after startStream
        // is called. These are used so that the thread calling startStream
        // blocks until it has begun running.
        // TODO: I've removed this all, moving the fl_thread to the ImageWindow class...
        // very likely I'll need to do something similarly hacky over there.
        //boost::mutex setup_lock;
        //boost::condition setup_notify;

        //window = new ImageWindow(256,192, (char*)"Robot Image");
        window = FLTKManager::get_image_window(256,192, (char*)"Robot Image");
        //imageWindow = new ImageWindow(0,0,256,192,NULL);
        window->end();
        window->set_color_mode(color_mode);
        //fl_thread = new Fl_Thread(window, setup_lock, setup_notify);
        shared_buffer = new circbuf(BUFFER_SIZE);
        display_thread = new DisplayThread(window, shared_buffer, filters, 
                                                                    filterLock);
        capture_thread = new CaptureThread(myScrib, shared_buffer, color_mode);

        //boost::mutex::scoped_lock l(setup_lock);
        capture_thread->start();
        display_thread->start();
        //fl_thread->start();
        running = true;
        // Wait until the fl_thread has actually started running
        //setup_notify.wait(l);
        //id = myScrib->registerVideoStream(this);
        //std::cerr << "Done StartStream()" << std::endl;
    }
}

int VideoStream::addFilter(Filter * filter) {
    boost::mutex::scoped_lock l(filterLock);
    //pthread_mutex_lock(filterLock);
    int result = 0;
    filters->push_back(filter);
    result = filters->size()-1;
    //pthread_mutex_unlock(filterLock);
    return result;
}

int VideoStream::delFilter(int filter_location) {
    if(filter_location < 0 || filter_location > (int)filters->size())
        return -1;

    boost::mutex::scoped_lock l(filterLock);
    filters->erase(filters->begin() + filter_location);

    return 0;
}

void VideoStream::endStream() {
    if ( running ){
        // Remove the window for the fltk mananager
        FLTKManager::remove_image_window(window);

        //fl_thread->stop();
        display_thread->stop();
        capture_thread->stop();

        display_thread->join();
        capture_thread->join();

        //delete imageWindow;
        delete window;
        // Free all the memory that is sitting on the buffer that hasn't been 
        // displayed.
        while ( !shared_buffer->isEmpty() ) free(shared_buffer->pop());
        delete shared_buffer;

        delete display_thread;
        delete capture_thread;
        running = false;
        //myScrib->unregisterVideoStream(id);
        id = -1;
    }
}

