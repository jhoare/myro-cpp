include_directories(${CMAKE_SOURCE_DIR}/headers)
#LINK_LIBRARIES(scribbler)
LINK_LIBRARIES(${Magick++_LIBRARY})
LINK_LIBRARIES(myro-cpp)

add_executable(myro_test_motor test_motor.cpp)
add_executable(myro_test_camera test_camera.cpp)
#add_executable(myro_test_blob test_blob.cpp)
add_executable(myro_video_stream video_stream.cpp)

#INSTALL(TARGETS myro_test_motor myro_test_camera myro_test_blob myro_video_stream RUNTIME DESTINATION bin)
INSTALL(TARGETS myro_test_motor myro_test_camera myro_video_stream RUNTIME DESTINATION bin)
