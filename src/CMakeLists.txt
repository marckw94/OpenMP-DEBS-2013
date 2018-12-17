cmake_minimum_required(VERSION 3.10)
project(Middleware)

set(CMAKE_CXX_STANDARD 17)

set(Boost_INCLUDE_DIR C:/MinGW/include/)
set(Boost_LIBRARY_DIR C:/MinGW/lib/)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
message(STATUS "Boost_VERSION: ${Boost_VERSION}")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()



add_executable(Middleware main.cpp Datas.cpp Datas.h Utils.cpp Utils.h Interruption.cpp Interruption.h fullGame.cpp fullGame.h Position.cpp Position.h Player.cpp Player.h Ball.cpp Ball.h)
target_link_libraries(Middleware ${Boost_LIBRARIES})
