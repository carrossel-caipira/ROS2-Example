cmake_minimum_required(VERSION 3.8)
project(sensor_filter)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(apresentacao_interfaces REQUIRED)

add_executable(telemetry_filter src/telemetry_filter.cpp)
ament_target_dependencies(telemetry_filter rclcpp apresentacao_interfaces)

install(TARGETS
  telemetry_filter
  DESTINATION lib/${PROJECT_NAME})

ament_package()
