Building On Cygwin
==================

As per main readme, building on cygwin requires the same dependencies:

  * Boost Threads (www.boost.org)
  * FLTK 1.1 (www.fltk.org)
  * libjpeg (www.ijg.org)

Cygwin Known Issues
===================

  1.) For the drawing elements to work, you must compile myro-cpp with the 
          version of fltk that uses the X11 window system (i.e. not native 
          windows drawing)
  2.) VideoStream will not function (as in the myro_video_stream, 
          myro_test_blob test executables) if the program is waiting on 
          console I/O. However, if a sleep() is inserted, instead of 
          cin >> foo; The VideoStream element will work fine. 
