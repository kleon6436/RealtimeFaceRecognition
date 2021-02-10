cmake_minimum_required(VERSION 3.17)
project(RealTimeFaceRecognition)

set(CMAKE_CXX_STANDARD 20)

add_executable(RealTimeFaceRecognition main.cpp)

set( OpenCV_DIR )
if(WIN32)
    if( NOT CMAKE_CL_64 )
        set( OpenCV_DIR "D:/ProgramLibrary/vcpkg/installed/x86-windows/share/opencv" )
    else()
        set( OpenCV_DIR "D:/ProgramLibrary/vcpkg/installed/x64-windows/share/opencv" )
    endif()
endif()
if(APPLE)
    set( OpenCV_DIR "/usr/local/lib/cmake/opencv4" )
endif()

find_package(OpenCV)

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

if (OpenCV_FOUND)
    # Additional Include Directories
    include_directories( ${OpenCV_INCLUDE_DIRS} )

    # Additional Library Directories
    link_directories( ${OpenCV_LIB_DIR} )

    # Additional Dependencies
    target_link_libraries( RealTimeFaceRecognition ${OpenCV_LIBS} )
endif()