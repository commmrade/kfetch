cmake_minimum_required(VERSION 3.5.0)
project(proj VERSION 0.1.0 LANGUAGES C CXX)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(proj main.cpp CPU.cpp GPU.cpp Desktop.cpp Kernel.cpp Packager.cpp logos.cpp)


target_include_directories(proj PUBLIC "${CMAKE_SOURCE_DIR}/include")


include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})


include(CPack)
