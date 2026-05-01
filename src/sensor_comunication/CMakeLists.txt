cmake_minimum_required(VERSION 3.8)
project(sensor_comunication)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(apresentacao_interfaces REQUIRED)

add_executable(sensor_emulator src/sensor_emulator.cpp)
ament_target_dependencies(sensor_emulator rclcpp apresentacao_interfaces)

add_executable(sensor_real src/sensor_real.cpp)
ament_target_dependencies(sensor_real rclcpp apresentacao_interfaces)

install(TARGETS
  sensor_emulator
  sensor_real
  DESTINATION lib/${PROJECT_NAME})

ament_package()
