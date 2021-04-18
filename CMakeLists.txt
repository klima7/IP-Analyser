cmake_minimum_required(VERSION 3.19)
project(IpAnalyser)

set(CMAKE_CXX_STANDARD 14)

add_executable(IpAnalyser main.cpp IpAddr.cpp IpAddr.h IpMask.cpp IpMask.h IpCompoundAddr.cpp IpCompoundAddr.h IpData.cpp IpData.h)