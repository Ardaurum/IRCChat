#-------------------------------------------------
#
# Project created by QtCreator 2015-01-25T15:02:49
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = IRCclient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Protocols/EnterProtocol.cpp \
    Protocols/ErrorProtocol.cpp \
    Protocols/ListProtocol.cpp \
    Protocols/Message.cpp \
    Protocols/MessageProtocol.cpp \
    Protocols/Protocol.cpp \
    Protocols/StandardProtocol.cpp

HEADERS  += mainwindow.h \
    Protocols/EnterProtocol.h \
    Protocols/ErrorProtocol.h \
    Protocols/ListProtocol.h \
    Protocols/Message.h \
    Protocols/MessageProtocol.h \
    Protocols/Protocol.h \
    Protocols/StandardProtocol.h

FORMS    += mainwindow.ui
