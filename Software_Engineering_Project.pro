TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

SOURCES += \
    Source/main.cpp \
    Source/Controller/FileManager.cpp \
    Source/Controller/DocumentManager.cpp \
    Source/Controller/Parser.cpp

RESOURCES += \
    $$PWD/Source/View/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = \
    $$PWD/Source/View

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    Source/Application.h \
    Source/Model/ApplicationData.h \
    Source/Model/Style.h \
    Source/Model/Document.h \
    Source/Controller/FileManager.h \
    Source/Controller/DocumentManager.h \
    Source/Controller/Parser.h

INCLUDEPATH = \
    $$PWD/Source \
    $$PWD/Source/View \
    $$PWD/Source/Model \
    $$PWD/Source/Controller
