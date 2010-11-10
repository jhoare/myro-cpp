INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/headers)

#LINK_LIBRARIES(${Magick++_LIBRARY})
LINK_LIBRARIES(${Boost_THREAD_LIBRARY})
LINK_LIBRARIES(${Magick++_LIBRARIES})

#ADD_LIBRARY(scribbler SHARED Myro.cpp Scribbler.cpp serial.cpp Robot.cpp ColorPicture.cpp GrayPicture.cpp Picture.cpp)
#ADD_LIBRARY(videostream SHARED VideoStream.cpp ImageWindow.cpp Filter.cpp)
ADD_LIBRARY(myro-cpp SHARED Myro.cpp MyroInternals.cpp Scribbler.cpp serial.cpp Robot.cpp ColorPicture.cpp GrayPicture.cpp Picture.cpp VideoStream.cpp ImageWindow.cpp Filter.cpp)

TARGET_LINK_LIBRARIES(myro-cpp ${FLTK_LIBRARIES})
#TARGET_LINK_LIBRARIES(videostream ${FLTK_LIBRARIES})
#TARGET_LINK_LIBRARIES(videostream scribbler)

INSTALL_TARGETS(/lib myro-cpp)

# Set up a pkg-config file 
CONFIGURE_FILE (${CMAKE_SOURCE_DIR}/cmake/pkgconfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/myro-cpp.pc @ONLY)
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/myro-cpp.pc 
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig
        COMPONENT pkgconfig)
