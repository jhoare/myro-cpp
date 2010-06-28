include_directories(${CMAKE_SOURCE_DIR}/headers)
#LINK_LIBRARIES(scribbler)
LINK_LIBRARIES(${Magick++_LIBRARY})
LINK_LIBRARIES(myro-cpp)

add_executable(test_motor test_motor.cpp)
add_executable(test_camera test_camera.cpp)
add_executable(test_blob test_blob.cpp)
add_executable(video_stream video_stream.cpp)
