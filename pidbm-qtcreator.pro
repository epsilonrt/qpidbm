TEMPLATE       = app
CONFIG += debug
QT           += sql
SOURCES     = \
             src/mainwindow.cpp\
             src/treemodel.cpp\
             src/actionbutton.cpp\
             src/node.cpp\
             src/main.cpp\

HEADERS     = \
             src/node.h\
             src/treemodel.h\
             src/mainwindow.h\
             src/actionbutton.h\

RESOURCES   = \
             pidbm.qrc\
