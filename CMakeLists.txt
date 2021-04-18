project(IpAnalyser)

set(CMAKE_CXX_STANDARD 14)

add_executable(IpAnalyser main.cpp ipaddr.cpp ipaddr.h ipmask.cpp ipmask.h ipcompaddr.cpp ipcompaddr.h ipdata.cpp ipdata.h ipexcept.h main.h)