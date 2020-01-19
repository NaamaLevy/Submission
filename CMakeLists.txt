cmake_minimum_required(VERSION 3.15)
project(Boost_Echo_Client)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

link_libraries("-lboost_system")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
add_executable(Boost_Echo_Client
        include/connectionHandler.h
        src/connectionHandler.cpp
        src/echoClient.cpp include/fromServer.h include/fromKB.h src/fromServer.cpp src/fromKB.cpp src/Client.cpp src/ClientData.cpp include/ClientData.h)
