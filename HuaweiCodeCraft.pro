QT += core
QT -= gui

CONFIG += c++11

TARGET = HuaweiCodeCraft
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    node.cpp \
    spring.cpp \
    graph.cpp

HEADERS += \
    node.h \
    spring.h \
    graph.h
