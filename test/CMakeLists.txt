include_directories(${CMAKE_SOURCE_DIR}/headers)
LINK_LIBRARIES(myro-cpp)

add_executable(myro_test_motor test_motor.cpp)
add_executable(myro_test_camera test_camera.cpp)
add_executable(myro_test_blob test_blob.cpp)
add_executable(myro_video_stream video_stream.cpp)

INSTALL(TARGETS myro_test_motor myro_test_camera myro_test_blob myro_video_stream RUNTIME DESTINATION bin)
#INSTALL(TARGETS myro_test_motor myro_test_camera myro_video_stream RUNTIME DESTINATION bin)

INSTALL( FILES README Makefile test_motor.cpp test_camera.cpp test_blob.cpp video_stream.cpp DESTINATION "share/myro-cpp-${PKG_VERSION}/examples" )
