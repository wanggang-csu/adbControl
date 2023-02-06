cmake_minimum_required(VERSION 2.8)
project(pubg)

set( CMAKE_BUILD_TYPE Release )
set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )

# 需要引入线程库
find_package(Threads REQUIRED)

# 库文件
include_directories(./include/adb)
add_library(adbcontrol SHARED
            ./src/adb/ADBControl.cpp)
# 把adbcontrol也链接上，这样后续如果类中也可以直接使用
target_link_libraries(adbcontrol pthread)


add_executable(main ./src/main.cpp)
target_link_libraries(main adbcontrol pthread)