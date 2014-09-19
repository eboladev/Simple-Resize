QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simple-resize
TEMPLATE = app

SOURCES += $$PWD/src/main.cpp\
    $$PWD/src/mainwindow.cpp \
    $$PWD/src/application.cpp \
    $$PWD/src/settings.cpp \
    $$PWD/src/specialspinbox.cpp

HEADERS  += $$PWD/src/mainwindow.h \
    $$PWD/src/application.h \
    $$PWD/src/settings.h \
    $$PWD/src/specialspinbox.h

FORMS += $$PWD/src/mainwindow.ui

RESOURCES += $$PWD/resources/resources.qrc

TRANSLATIONS = $$PWD/resources/translations/simple-resize_ru.ts
OTHER_FILES = $$PWD/resources/translations/simple-resize_ru.ts
