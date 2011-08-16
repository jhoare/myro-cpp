include_directories(${CMAKE_SOURCE_DIR}/headers)
LINK_LIBRARIES(myro-cpp)

add_executable(myro_graphwin_test graphwin_test.cpp)
add_executable(myro_polygon_test polygon_test.cpp)
add_executable(myro_circles circles.cpp)
add_executable(myro_joystick robot_joystick.cpp)
add_executable(myro_senses robot_senses.cpp)
