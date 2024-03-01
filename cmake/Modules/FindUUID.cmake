# Copyright 2024 Open Source Robotics Foundation, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Try to find uuid
# Once done, this will define
#
# UUID_FOUND        - system has uuid
# UUID_INCLUDE_DIRS - uuid include directories
# UUID_LIBRARIES    - libraries needed to use uuid
#
# and the following imported target
#
# UUID::UUID

find_package(PkgConfig)
pkg_check_modules(PC_uuid QUIET uuid)
set(UUID_VERSION ${PC_uuid_VERSION})

find_path(UUID_INCLUDE_DIR
  NAMES uuid.h
  HINTS ${UUID_ROOT} ${PC_uuid_INCLUDEDIR} ${PC_uuid_INCLUDE_DIRS}
  PATH_SUFFIXES include uuid)

find_library(UUID_LIBRARY
  NAMES uuid
  HINTS ${UUID_ROOT} ${PC_uuid_LIBDIR} ${PC_uuid_LIBRARY_DIRS}
  PATH_SUFFIXES ${CMAKE_INSTALL_LIBDIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(UUID
  REQUIRED_VARS UUID_LIBRARY UUID_INCLUDE_DIR
  VERSION_VAR UUID_VERSION)

if(UUID_FOUND AND NOT TARGET UUID::UUID)
  mark_as_advanced(UUID_FOUND UUID_INCLUDE_DIR UUID_LIBRARY)
  add_library(UUID::UUID UNKNOWN IMPORTED)
  set_target_properties(UUID::UUID PROPERTIES
    IMPORTED_LOCATION "${UUID_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${UUID_INCLUDE_DIR}")
endif()

set(UUID_INCLUDE_DIRS ${UUID_INCLUDE_DIR})
set(UUID_LIBRARIES ${UUID_LIBRARY})
unset(UUID_INCLUDE_DIR)
unset(UUID_LIBRARY)
