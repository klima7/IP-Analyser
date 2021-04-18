cmake_minimum_required(VERSION 3.19)
project(IpAnalyser)

set(CMAKE_CXX_STANDARD 17)

add_executable(IpAnalyser main.cpp ipaddr.cpp ipaddr.h ipmask.cpp ipmask.h ipcompaddr.cpp ipcompaddr.h ipdata.cpp ipdata.h ipexcept.h main.h)