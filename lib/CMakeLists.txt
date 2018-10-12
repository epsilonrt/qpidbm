# lib/CMakeLists.txt
project(${LIB_NAME})

file(GLOB_RECURSE LIB_SOURCES *.cpp)

add_library(${LIB_NAME} ${LIB_SOURCES} ${PROJECT_RCC_FILE})
target_link_libraries(${LIB_NAME} Qt4::QtGui Qt4::QtSql)
