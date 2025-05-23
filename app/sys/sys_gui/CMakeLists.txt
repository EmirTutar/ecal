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

cmake_minimum_required(VERSION 3.14)

# Allow the install command to use generator expressions
if(POLICY CMP0087)
    cmake_policy(SET CMP0087 NEW)
endif()

set(PROJECT_NAME sys_gui)

# Legacy Qt5 (pre 5.15) support as suggested by teh Qt Documentation:
# https://doc.qt.io/qt-6/cmake-qt5-and-qt6-compatibility.html#supporting-older-qt-5-versions
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

find_package(tclap REQUIRED)
find_package(Protobuf REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC OFF) # Reason for being turned off: AutoUIC will prevent VS from detecting changes in .ui files
set(CMAKE_AUTORCC OFF) # Reason for being turned off: AutoRCC will create an entirely new project in VS which clutters the solution appearance. Additionally, we cannot assign a source group to the generated .cpp files which will clutter the project.
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(source_files
    src/ecalsys_gui.cpp
    src/ecalsys_gui.h
    src/ecalsys_service.cpp
    src/ecalsys_service.h
    src/globals.h
    src/help_window.cpp
    src/help_window.h
    src/main.cpp

    src/widgets/about_dialog/about_dialog.cpp
    src/widgets/about_dialog/about_dialog.h

    src/widgets/groupwidget/group_widget.cpp
    src/widgets/groupwidget/group_widget.h

    src/widgets/group_edit_widget/group_edit_widget.cpp
    src/widgets/group_edit_widget/group_edit_widget.h
    src/widgets/group_edit_widget/severity_picker_delegate.cpp
    src/widgets/group_edit_widget/severity_picker_delegate.h

    src/widgets/import_from_cloud_widget/import_from_cloud_widget.cpp
    src/widgets/import_from_cloud_widget/import_from_cloud_widget.h
    src/widgets/import_from_cloud_widget/import_from_cloud_window.cpp
    src/widgets/import_from_cloud_widget/import_from_cloud_window.h

    src/widgets/license_dialog/license_dialog.cpp
    src/widgets/license_dialog/license_dialog.h

    src/widgets/mmawidget/mma_host_item.cpp
    src/widgets/mmawidget/mma_host_item.h
    src/widgets/mmawidget/mma_widget.cpp
    src/widgets/mmawidget/mma_widget.h
    src/widgets/mmawidget/multi_label_item.cpp
    src/widgets/mmawidget/multi_label_item.h
    src/widgets/mmawidget/resource_bar.h
    src/widgets/mmawidget/tree_widget_item_types.h

    src/widgets/runnerwidget/runner_widget.cpp
    src/widgets/runnerwidget/runner_widget.h
    src/widgets/runnerwidget/runner_window.cpp
    src/widgets/runnerwidget/runner_window.h

    src/widgets/severity_model/severity_level_model.cpp
    src/widgets/severity_model/severity_level_model.h
    src/widgets/severity_model/severity_model.cpp
    src/widgets/severity_model/severity_model.h

    src/widgets/targets_reachable_dialog/targets_reachable_dialog.cpp
    src/widgets/targets_reachable_dialog/targets_reachable_dialog.h

    src/widgets/taskwidget/task_widget.cpp
    src/widgets/taskwidget/task_widget.h

    src/widgets/treemodels/group_state_min_task_state_tree_item.cpp
    src/widgets/treemodels/group_state_min_task_state_tree_item.h
    src/widgets/treemodels/group_state_min_task_state_tree_model.cpp
    src/widgets/treemodels/group_state_min_task_state_tree_model.h
    src/widgets/treemodels/group_state_tree_item.cpp
    src/widgets/treemodels/group_state_tree_item.h
    src/widgets/treemodels/group_state_tree_model.cpp
    src/widgets/treemodels/group_state_tree_model.h
    src/widgets/treemodels/group_tree_item.cpp
    src/widgets/treemodels/group_tree_item.h
    src/widgets/treemodels/group_tree_model.cpp
    src/widgets/treemodels/group_tree_model.h
    src/widgets/treemodels/import_from_cloud_runner_tree_model.cpp
    src/widgets/treemodels/import_from_cloud_runner_tree_model.h
    src/widgets/treemodels/import_from_cloud_task_tree_model.cpp
    src/widgets/treemodels/import_from_cloud_task_tree_model.h
    src/widgets/treemodels/runner_tree_item.cpp
    src/widgets/treemodels/runner_tree_item.h
    src/widgets/treemodels/runner_tree_model.cpp
    src/widgets/treemodels/runner_tree_model.h
    src/widgets/treemodels/task_tree_item.cpp
    src/widgets/treemodels/task_tree_item.h
    src/widgets/treemodels/task_tree_model.cpp
    src/widgets/treemodels/task_tree_model.h
    src/widgets/treemodels/tree_data_roles.h
    src/widgets/treemodels/tree_item_types.h
)
set(qt_resource_files
    ../../iconset/ecalicons.qrc
    resources/resources.qrc
)
if(WIN32)
    set(win32_resource_files
        resources/resource.h
        resources/win32_resources.rc
    )
endif(WIN32)

set(ui_files
    src/help_window.ui
    src/main_window.ui
    src/widgets/about_dialog/about_dialog.ui
    src/widgets/groupwidget/group_widget.ui
    src/widgets/group_edit_widget/group_edit_widget.ui
    src/widgets/import_from_cloud_widget/import_from_cloud_widget.ui
    src/widgets/import_from_cloud_widget/import_from_cloud_window.ui
    src/widgets/license_dialog/license_dialog.ui
    src/widgets/mmawidget/mma_widget.ui
    src/widgets/mmawidget/resource_bar.ui
    src/widgets/runnerwidget/runner_widget.ui
    src/widgets/runnerwidget/runner_window.ui
    src/widgets/targets_reachable_dialog/targets_reachable_dialog.ui
    src/widgets/taskwidget/task_widget.ui
)

if(UNIX)
  #set_source_files_properties(src/convert_utf.cpp PROPERTIES COMPILE_FLAGS -Wno-implicit-fallthrough)
endif()

# compile qt resource files and ui files
if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_resources(autogen_resources ${qt_resource_files})
    qt_wrap_ui      (autogen_ui        ${ui_files})
else()
    qt5_add_resources(autogen_resources ${qt_resource_files})
    qt5_wrap_ui      (autogen_ui        ${ui_files})
endif()


# Add all files. The resource files and ui files are not necessary, but we want them to show up in the IDE
ecal_add_app_qt(${PROJECT_NAME} 
    ${source_files}
    ${qt_resource_files}
    ${win32_resource_files}
    ${ui_files}

    ${autogen_resources}
    ${autogen_ui}
)

create_targets_protobuf() 

target_link_libraries (${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    CustomQt
    CustomTclap
    tclap::tclap
    eCAL::core
    eCAL::sys_core
    protobuf::libprotobuf
    EcalParser
    QEcalParser
    eCAL::ecal-utils
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)

target_compile_definitions(${PROJECT_NAME} PRIVATE 
  ECAL_VERSION="${eCAL_COMPLETE_VERSION}"
  ECAL_DATE="${eCAL_DATE}"
)

if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
      LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
      LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE"
      LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
      LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()
if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/wd4127 /wd4714")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_include_directories(${PROJECT_NAME} PRIVATE $<TARGET_PROPERTY:eCAL::core,INCLUDE_DIRECTORIES>)

if ((WIN32 OR APPLE) AND (${QT_VERSION_MAJOR} GREATER_EQUAL 6))

    # Generate a script that will deploy all necessary Qt DLLs to the binary folder
    # https://doc.qt.io/qt-6/qt-deploy-runtime-dependencies.html
    # Available for Qt 6.3 and up (=> Not for Qt5!)
    # Executing it requires CMake 3.14 and up, due to policy https://cmake.org/cmake/help/latest/policy/CMP0087.html
    qt_generate_deploy_app_script(
        TARGET ${PROJECT_NAME}
        OUTPUT_SCRIPT qt_deploy_script
        NO_COMPILER_RUNTIME
        NO_UNSUPPORTED_PLATFORM_ERROR
    )

    # Add a postbuild script that will also execute the created script via cmake -P
    # This is necessary to make the application startable / debuggable from the build directory.
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -DQT_DEPLOY_PREFIX=$<TARGET_FILE_DIR:${PROJECT_NAME}> -DQT_DEPLOY_BIN_DIR=. -P ${qt_deploy_script}
    )

    # Use the script for deploying the qt dlls in the install dir
    install(SCRIPT ${qt_deploy_script})

elseif(WIN32)

    # For Qt5 we use our legacy script.
    # Deploy Qt DLLs in the binary folder. This is necessary for starting the application from whithin the IDE without having to copy QtCore.dll, QtWidgets.dll etc. by hand each time
    qt_add_windeployqt_postbuild(--no-system-d3d-compiler --no-compiler-runtime --no-opengl-sw --pdb "$<TARGET_FILE:${PROJECT_NAME}>")

endif()

# Create a source tree that mirrors the filesystem
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}"
    FILES
        ${source_files}
        ${win32_resource_files}
        ${ui_files}
)

source_group(resources FILES
    ${qt_resource_files}
)

# Also create a group for autogenerated files. The autogenerated ui files are not necessary as they are only header files. We add them anyhow, just for completeness.
source_group( autogen FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_automoc.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_autogen/mocs_compilation.cpp
    ${autogen_ui}
    ${autogen_resources}
)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER app/sys)

# install files required for linux mimetypes and icon
if (UNIX)
    INSTALL (FILES "${CMAKE_CURRENT_LIST_DIR}/mimetype/ecal-sys.xml"
            DESTINATION "${CMAKE_INSTALL_DATADIR}/mime/packages/")

    INSTALL (FILES "${CMAKE_CURRENT_LIST_DIR}/mimetype/application-ecalsys.svg"
            DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/Humanity/scalable/mimetypes/")
endif()

ecal_install_app(${PROJECT_NAME} START_MENU_NAME "eCAL Sys")