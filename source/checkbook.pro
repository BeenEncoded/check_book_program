QT       += core gui widgets

CONFIG += C++14 debug

LIBS += /usr/lib/libboost_system.a /usr/lib/libboost_filesystem.a /usr/lib/libboost_regex.a

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Checkbook_Program
TEMPLATE = app

SOURCES += main.cpp \
            gui/MainWindow.cpp \
            gui/main_widgets/ManageAccounts.cpp

HEADERS  += gui/MainWindow.hpp \
            gui/main_widgets/ManageAccounts.hpp

FORMS    += gui/MainWindow.ui \
            gui/main_widgets/ManageAccounts.ui

#RESOURCES += 

CONFIG(debug, debug|release) {
    message(DEBUG BUILD)
    DESTDIR = debug
}

CONFIG(release, debug|release) {
    message(RELEASE BUILD)
    DESTDIR = release
}

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui
