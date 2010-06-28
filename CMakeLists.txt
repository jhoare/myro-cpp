CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
# Include this File to help us to search for dependencies
INCLUDE(${CMAKE_SOURCE_DIR}/cmake/LibFindMacros.cmake)
#
#
# Name the Project
PROJECT(Myro-Cpp)

#set(CMAKE_CXX_FLAGS "-g -Wall")

FIND_PACKAGE(FLTK REQUIRED)
INCLUDE_DIRECTORIES(${FLTK_INCLUDE_DIRS})


set(Boost_DEBUG TRUE)
set(Boost_USE_STATIC_LIBS ON)
# Check for Boost Threading Library
#FIND_PACKAGE(BOOST REQUIRED)
set(Boost_USE_MULTITHREADED ON)
set(Boost_DETAILED_FAILURE_MSG TRUE)
FIND_PACKAGE(BOOST 1.41.0 COMPONENTS thread NO_MODULE)
MESSAGE(STATUS "INCLUDES: ${Boost_INCLUDE_DIRS}")
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
set (Boost_THREAD_LIBRARY boost_thread-mt)
#MESSAGE(STATUS "Threading Found?: ${Boost_THREAD_FOUND}")
#MESSAGE(STATUS "LIBRARIES: ${Boost_LIBRARIES}")
#MESSAGE(STATUS "Thread: ${Boost_THREAD_LIBRARY}")

# Search for Magick++
# - Try to find ImageMagick++
# Once done, this will define
#
#  Magick++_FOUND - system has Magick++
#  Magick++_INCLUDE_DIRS - the Magick++ include directories
#  Magick++_LIBRARIES - link these to use Magick++

# Dependencies
libfind_package(Magick++ Magick QUIET)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(Magick++_PKGCONF ImageMagick++)

# Include dir
find_path(Magick++_INCLUDE_DIR
  NAMES Magick++.h
  PATHS ${Magick++_PKGCONF_INCLUDE_DIRS}
)

# Finally the library itself
find_library(Magick++_LIBRARY
  NAMES Magick++ 
  PATHS ${Magick++_PKGCONF_LIBRARY_DIRS}
)

find_library(MagickCore_LIBRARY
  NAMES MagickCore
  PATHS ${Magick++_PKGCONF_LIBRARY_DIRS}
)
MESSAGE(STATUS "MagickCore_LIBRARY = ${MagickCore_LIBRARY}")


# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(Magick++_PROCESS_INCLUDES Magick++_INCLUDE_DIR Magick_INCLUDE_DIRS)
set(Magick++_PROCESS_LIBS Magick++_LIBRARY MagickCore_LIBRARY Magick_LIBRARIES)
libfind_process(Magick++)
INCLUDE_DIRECTORIES(${Magick++_INCLUDE_DIR})

add_subdirectory(src)
add_subdirectory(headers)
add_subdirectory(test)
