cmake_minimum_required(VERSION 3.5)
project(unique_identifier_msgs)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # we dont use add_compile_options with pedantic in message packages
  # because the Python C extensions dont comply with it
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif()

find_package(ament_cmake REQUIRED)
# Depend on "core" generators instead of "default" generators
# because ROS actions depend on this package
find_package(rosidl_core_generators REQUIRED)

set(msg_files
  "msg/UUID.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME} ${msg_files})

rosidl_get_typesupport_target(cpp_typesupport_target "${PROJECT_NAME}" "rosidl_typesupport_cpp")

ament_export_dependencies(rosidl_core_runtime)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

if(cpp_typesupport_target)
  list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")
  find_package(UUID REQUIRED)
  add_library(${PROJECT_NAME}_library INTERFACE)
  target_include_directories(${PROJECT_NAME}_library INTERFACE
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include/${PROJECT_NAME}>")
  target_link_libraries(${PROJECT_NAME}_library
    INTERFACE
      "${cpp_typesupport_target}"
      UUID::UUID
  )

  install(DIRECTORY include/
    DESTINATION include/${PROJECT_NAME}
  )
  install(
    TARGETS ${PROJECT_NAME}_library EXPORT export_${PROJECT_NAME}
  )
  install(DIRECTORY cmake DESTINATION share/${PROJECT_NAME})

  # Export old-style CMake variables
  ament_export_include_directories("include/${PROJECT_NAME}")

  # Export modern CMake targets
  ament_export_targets(export_${PROJECT_NAME})

  ament_export_dependencies(UUID)

  if(BUILD_TESTING)
    ament_add_gtest(test_${PROJECT_NAME}
      test/test_uuid_coversion.cpp
    )
    target_link_libraries(test_${PROJECT_NAME} ${PROJECT_NAME}_library)
  endif()
endif()

ament_package(
  CONFIG_EXTRAS "unique_identifier_msgs-extras.cmake"
)

install(
  FILES mapping_rules.yaml
  DESTINATION share/${PROJECT_NAME})
