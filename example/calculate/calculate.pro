LANGUAGE = C++
QT -= gui
CONFIG += release console
LIBS += -L../../build/ -ljfuzzyqt
UI_DIR = ./src.gen/ui
MOC_DIR = ./src.gen/moc
OBJECTS_DIR = ./src.gen/obj
DESTDIR = ../../build
TARGET = calculate
DEPENDPATH += .
INCLUDEPATH += ../../include
win32-msvc|win32-msvc.net|win32-msvc2002|win32-msvc2003|win32-msvc2005|win32-msvc2008 {
    TEMPLATE = vcapp
} else {
    TEMPLATE = app
}
DEPENDPATH += .
INCLUDEPATH += .
SOURCES += main.cpp
