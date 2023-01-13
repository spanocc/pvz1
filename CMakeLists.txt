cmake_minimum_required(VERSION 3.5)

project(PVZ1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/home/llh/Qt5.14.0/5.14.0/gcc_64")

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

# 将include目录添加到编译器用来搜索包含文件的目录中
include_directories("${PROJECT_SOURCE_DIR}/include")

if(ANDROID)
  add_library(PVZ1 SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
  )
else()
  add_executable(PVZ1
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    rsc.qrc
    sun.cpp
    graph_block.cpp
    graph.cpp
    seedbank.cpp
    plantcard.cpp
    plant.cpp
    sunflower.cpp
    peashooter.cpp
  )
endif()

target_link_libraries(PVZ1 PRIVATE Qt5::Widgets)
