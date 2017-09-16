#-------------------------------------------------
#
# Project created by QtCreator 2013-09-12T03:27:41
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DisplayMesh
TEMPLATE = app

LIBS += /Users/crymsius/Library/Developer/Xcode/DerivedData/GeomMath-fkdxzhxqrjmmsieyiskltxurkbre/Build/Products/Debug/libGeomMath.a

SOURCES += main.cpp\
        mainwindow.cpp \
    gldisplay.cpp

HEADERS  += mainwindow.h \
    gldisplay.h

FORMS    += mainwindow.ui
