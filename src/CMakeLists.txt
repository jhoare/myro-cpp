INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/headers)

LINK_LIBRARIES(${Boost_THREAD_LIBRARY})

#ADD_LIBRARY(scribbler SHARED Myro.cpp Scribbler.cpp serial.cpp Robot.cpp ColorPicture.cpp GrayPicture.cpp Picture.cpp)
#ADD_LIBRARY(videostream SHARED VideoStream.cpp ImageWindow.cpp Filter.cpp)
ADD_LIBRARY(myro-cpp SHARED Myro.cpp MyroInternals.cpp Scribbler.cpp serial.cpp Robot.cpp ColorPicture.cpp GrayPicture.cpp Picture.cpp VideoStream.cpp ImageWindow.cpp Filter.cpp jmemsrc.c)

TARGET_LINK_LIBRARIES(myro-cpp ${FLTK_LIBRARIES} ${JPEG_LIBRARIES})
#TARGET_LINK_LIBRARIES(videostream ${FLTK_LIBRARIES})
#TARGET_LINK_LIBRARIES(videostream scribbler)

INSTALL_TARGETS(/lib myro-cpp)

# Set up a pkg-config file 
CONFIGURE_FILE (${CMAKE_SOURCE_DIR}/cmake/pkgconfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/myro-cpp.pc @ONLY)
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/myro-cpp.pc 
        DESTINATION /lib/pkgconfig
        COMPONENT pkgconfig)

CONFIGURE_FILE (${CMAKE_SOURCE_DIR}/cmake/myro-cpp-config.cmake ${CMAKE_CURRENT_BINARY_DIR}/myro-cpp-config @ONLY)
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/myro-cpp-config
        DESTINATION /bin
        COMPONENT myro-cpp-config
        PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
