cmake_minimum_required(VERSION 3.0.2)

## Use the variable PROJECT_NAME for changing the target name
set(PROJECT_NAME "pidbm")
set(LIB_TARGET "${PROJECT_NAME}")
set(BIN_TARGET "${PROJECT_NAME}-bin")

## Set our project name
project(${PROJECT_NAME})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Appends the cmake/modules path to MAKE_MODULE_PATH variable.
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(Qt4 4.8 REQUIRED QtGui QtSql)

include(GitVersion)
GetGitVersion(PIDBM_VERSION)
set(PIDBM_VERSION
  ${PIDBM_VERSION_MAJOR}.${PIDBM_VERSION_MINOR}.${PIDBM_VERSION_PATCH})
WriteGitVersionFile(${CMAKE_BINARY_DIR}/version.h)

include_directories(${CMAKE_SOURCE_DIR}/lib)
include_directories(${CMAKE_BINARY_DIR})
link_directories(${CMAKE_BINARY_DIR}/lib)

set(PROJECT_RCC_FILE "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}.qrc")
configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h")

add_subdirectory(lib)
add_subdirectory(main)
