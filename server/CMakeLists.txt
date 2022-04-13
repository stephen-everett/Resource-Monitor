cmake_minimum_required(VERSION 3.5)

project(SocketServerWithClasses LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SocketServerWithClasses main.cpp sensordata.h sensordata.cpp sockethandler.h sockethandler.cpp)
