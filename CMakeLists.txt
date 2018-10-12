cmake_minimum_required(VERSION 3.0.2)

## Use the variable PROJECT_NAME for changing the target name
set(PROJECT_NAME "pidbm")
set(LIB_NAME "lib${PROJECT_NAME}")

## Set our project name
project(${PROJECT_NAME})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt4 4.8 REQUIRED QtGui QtSql)

include_directories(${CMAKE_SOURCE_DIR}/lib)

set(PROJECT_RCC_FILE "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}.qrc")
configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h")

add_subdirectory(lib)
add_subdirectory(main)
