cmake_minimum_required(VERSION 3.10)
project(test_package)

## Use C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## By adding -Wall and -Werror, the compiler does not ignore warnings anymore,
## enforcing cleaner code.
add_definitions(-Wall -Werror)

## Find catkin macros and libraries
find_package(catkin REQUIRED
  COMPONENTS
    roscpp
    std_msgs
)

###################################
## catkin specific configuration ##
###################################
catkin_package(
  INCLUDE_DIRS
    include
  CATKIN_DEPENDS
    roscpp
    std_msgs
)

###########
## Build ##
###########
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

## Declare Executables (nodes)
add_executable(hello_world 
               src/hello_world_node.cpp)
target_link_libraries(hello_world ${catkin_LIBRARIES})

add_executable(talker 
               src/talker.cpp)
target_link_libraries(talker ${catkin_LIBRARIES})

add_executable(listener 
               src/listener.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})

add_executable(callback_threads 
               src/callback_threads.cpp)
target_link_libraries(callback_threads ${catkin_LIBRARIES})


