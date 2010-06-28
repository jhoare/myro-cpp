INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/headers)

#LINK_LIBRARIES(${Magick++_LIBRARY})
LINK_LIBRARIES(${Boost_THREAD_LIBRARY})
LINK_LIBRARIES(${Magick++_LIBRARIES})

#ADD_LIBRARY(scribbler SHARED Myro.cpp Scribbler.cpp serial.cpp Robot.cpp ColorPicture.cpp GrayPicture.cpp Picture.cpp)
#ADD_LIBRARY(videostream SHARED VideoStream.cpp ImageWindow.cpp Filter.cpp)
ADD_LIBRARY(myro-cpp SHARED Myro.cpp Scribbler.cpp serial.cpp Robot.cpp ColorPicture.cpp GrayPicture.cpp Picture.cpp VideoStream.cpp ImageWindow.cpp Filter.cpp)

TARGET_LINK_LIBRARIES(myro-cpp ${FLTK_LIBRARIES})
#TARGET_LINK_LIBRARIES(videostream ${FLTK_LIBRARIES})
#TARGET_LINK_LIBRARIES(videostream scribbler)

install_targets(lib myro-cpp)
