#-------------------------------------------------
#
# Project created by QtCreator 2012-05-09T22:09:20
#
#-------------------------------------------------

QT       += core gui
QT       += network

TARGET = Server_Graphics
TEMPLATE = app


SOURCES += main.cpp\
        server.cpp \
    tcpserver.cpp \
    thread.cpp \
    parser.cpp

HEADERS  += server.h \
    tcpserver.h \
    thread.h \
    parser.h

FORMS    += server.ui














