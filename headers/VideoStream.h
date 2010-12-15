#ifndef __VIDEOSTREAM_H__
#define __VIDEOSTREAM_H__

#include <Scribbler.h>
#include <Filter.h>
#include <ImageWindow.h>
#include <MyroForwardDec.h>


/**
 * @class VideoStream
 *
 * @brief A class for streaming video from a scribbler robot.
 *
 * The class is used to stream video from the robot and apply
 * filters to the video stream, so that the effects can be 
 * seen in real time.
 *
 * @author Richard Edwards
 * @author John Hoare
 */

class VideoStream {

    public:
    /// The possible color modes for the VideoStream
    enum color_mode { GRAY=0, COLOR=1, BLOB=2 };

    /**
     * @param scrib - A pointer to a scribbler robot instance.
     * @param color_mode - 0 If the stream is operating in gray scale
     * 1 if the stream is operating in RGB color space, and 2 if the
     * robot is taking blob images.
     */
    VideoStream(Scribbler * scrib, int color_mode);
    /**
     * @param scrib - A reference to a scribbler robot instance.
     * @param color_mode - 0 If the stream is operating in gray scale
     * 1 if the stream is operating in RGB color space, and 2 if the
     * robot is taking blob images.
     */
    VideoStream(Scribbler&  scrib, int color_mode);
    ~VideoStream();

    /**
     * Starts the stream in the background. Note, this function
     * should not be called if the scrib instance has not successfully
     * connected to a scribbler robot.
     */
    void startStream();

    /**
     * Used to add a filter to the video stream's filter list. Note
     * filters can be added at anytime to the video stream, even
     * during streaming.
     *
     * @return The index at which the filter was stored in the
     * video stream filter vector.
     */
    int addFilter(Filter * filter);

    /**
     * Used to delete a filter from the video stream's filter list
     * at a specified index.
     *
     * @return 0 for success, -1 for invalid index.
     */
    int delFilter(int filter_location);

    /**
     * Not yet fully functional, does not close the GUI.
     *
     * However, it does close the display and capture threads.
     */
    void endStream();

    private:
    int id;

    std::vector<Filter*> * filters;
    Scribbler * myScrib;
    int color_mode;

    //Fl_Window * window;
    ImageWindow * window;
    Fl_Thread * fl_thread;
    DisplayThread * display_thread;
    CaptureThread * capture_thread;
    circbuf * shared_buffer;

    boost::mutex* filterLock;

    bool running;
};


#endif
