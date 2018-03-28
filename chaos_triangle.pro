######################################################################
# chaos_triangle.pro
######################################################################

QT += widgets

QMAKE_PROJECT_NAME = chaos_triangle

INCLUDEPATH += .
QMAKE_CXXFLAGS += -Wextra -pedantic -std=c++11

# Input
HEADERS += window.h
SOURCES += main.cpp window.cpp
