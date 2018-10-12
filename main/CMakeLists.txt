# main/CMakeLists.txt

file(GLOB_RECURSE MAIN_SOURCES *.cpp)

add_executable(${PROJECT_NAME} ${MAIN_SOURCES} ${PROJECT_RCC_FILE})
target_link_libraries(${PROJECT_NAME} ${LIB_NAME} Qt4::QtGui Qt4::QtSql)
