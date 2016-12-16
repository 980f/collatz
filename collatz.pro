QT += core
QT -= gui

CONFIG += c++11

TARGET = collatz
CONFIG += console
CONFIG -= app_bundle

DEFINES += QT_NO_DEPRECATED
#when I defined no_deprecated then a clause dependent upon no_translation created a compilation fault
DEFINES += QT_NO_TRANSLATION



TEMPLATE = app

SOURCES += main.cpp
