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
cmake_minimum_required(VERSION 3.15)

# --------------------------------------------------------
# c samples
# --------------------------------------------------------
# pubsub
add_subdirectory(pubsub/string/hello_send)
add_subdirectory(pubsub/string/hello_receive)
add_subdirectory(pubsub/binary/blob_send)
add_subdirectory(pubsub/binary/blob_receive)

#service
add_subdirectory(services/mirror_client_c)
add_subdirectory(services/mirror_server_c)

# misc
add_subdirectory(misc/cake_send)
add_subdirectory(misc/cake_receive)