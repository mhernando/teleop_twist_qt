cmake_minimum_required(VERSION 3.5)
project(teleop_twist_qt)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -fPIC)
endif()
#ADD_DEFINITIONS(-DBUILD_VERSION=”${BUILD_VERSION}” )

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
#find_package(rmw_implementation REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

find_package(Qt5 COMPONENTS Core Widgets Gamepad REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(
 ${rclcpp_INCLUDE_DIRS}
 ${std_msgs_INCLUDE_DIRS}
 ${PROJECT_SOURCE_DIR}/src
 )
file(GLOB SOURCE_FILES
 ${PROJECT_SOURCE_DIR}/src/*.cpp
 )
 file(GLOB UI_SOURCE_FILES
 ${PROJECT_SOURCE_DIR}/src/*.ui
 )
  file(GLOB RC_SOURCE_FILES
 ${PROJECT_SOURCE_DIR}/src/*.qrc
 )

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${UI_SOURCE_FILES} ${RC_SOURCE_FILES})
ament_target_dependencies(${PROJECT_NAME}
 rclcpp
 std_msgs
 geometry_msgs
 #rmw_implementation
 )

target_link_libraries(${PROJECT_NAME}
 Qt5::Widgets Qt5::Core Qt5::Gamepad
 )
 
 install(TARGETS
  ${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME})
  
install(TARGETS ${PROJECT_NAME} 
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  )
 
ament_package()
