# ========================= eCAL LICENSE =================================
#
# Copyright (C) 2016 - 2025 Continental Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#      http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# ========================= eCAL LICENSE =================================

add_library(message_base INTERFACE)
add_library(eCAL::message_base ALIAS message_base)

target_sources(message_base
  INTERFACE
    FILE_SET message_base_headers
    TYPE HEADERS
    BASE_DIRS include
    FILES
      include/ecal/msg/exception.h
)

target_compile_features(message_base INTERFACE cxx_std_14)

install(
  TARGETS message_base
  EXPORT eCALCoreTargets  
  FILE_SET message_base_headers COMPONENT sdk
)


################################
# eCAL core Message extensions #
################################
add_library(message_core INTERFACE)
add_library(eCAL::message_core ALIAS message_core)

target_link_libraries(message_core 
  INTERFACE 
    eCAL::core
)

target_sources(message_core
  INTERFACE
    FILE_SET message_core_headers
    TYPE HEADERS
    BASE_DIRS include
    FILES
      include/ecal/msg/publisher.h
      include/ecal/msg/subscriber.h
)

target_compile_features(message_core INTERFACE cxx_std_14)

install(
  TARGETS message_core
  EXPORT eCALCoreTargets  
  ARCHIVE       DESTINATION "${eCAL_install_archive_dir}" COMPONENT sdk
  LIBRARY       DESTINATION "${eCAL_install_lib_dir}"     COMPONENT sdk
  FILE_SET message_core_headers COMPONENT sdk
)

#######################################
# eCAL measurement message extensions #
#######################################
add_library(message_measurement INTERFACE)
add_library(eCAL::message_measurement ALIAS message_measurement)

target_link_libraries(message_measurement 
  INTERFACE 
    eCAL::measurement
)

target_sources(message_measurement
  INTERFACE
    FILE_SET message_measurement_headers
    TYPE HEADERS
    BASE_DIRS include
    FILES
      include/ecal/msg/imeasurement.h
      include/ecal/msg/omeasurement.h
)

target_compile_features(message_measurement INTERFACE cxx_std_14)

install(
  TARGETS message_measurement
  EXPORT eCALCoreTargets  
  ARCHIVE       DESTINATION "${eCAL_install_archive_dir}" COMPONENT sdk
  LIBRARY       DESTINATION "${eCAL_install_lib_dir}"     COMPONENT sdk
  FILE_SET message_measurement_headers COMPONENT sdk
)

