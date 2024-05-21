cmake_minimum_required(VERSION 3.5)
project(cppOpencv_test)

find_package(OpenCV REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src/lib 
)


add_executable(
    main src/main.cpp 
    src/lib/perspective.cpp
    src/lib/cv_wrapper.cpp

)
target_link_libraries(main ${OpenCV_LIBS})
