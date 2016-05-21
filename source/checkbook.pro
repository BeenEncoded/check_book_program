QT       += core gui widgets

CONFIG += C++14 debug

QMAKE_CXXFLAGS += /IC:\Users\include #additional includes

#release libs
CONFIG(release, debug|release) {
	LIBS += "C:\lib\x64\libboost_system-vc140-mt-1_60.lib" \
			"C:\lib\x64\libboost_filesystem-vc140-mt-1_60.lib" \
			"C:\lib\x64\libboost_regex-vc140-mt-1_60.lib"
}

#debug libs
CONFIG(debug, debug|release) {
	LIBS += "C:\lib\x64\libboost_system-vc140-mt-gd-1_60.lib" \
			"C:\lib\x64\libboost_filesystem-vc140-mt-gd-1_60.lib" \
			"C:\lib\x64\libboost_regex-vc140-mt-gd-1_60.lib"
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = checkbook_program
TEMPLATE = app

SOURCES += main.cpp \
			data/global.cpp \
            gui/MainWindow.cpp \
            gui/main_widgets/ManageAccounts.cpp \
            gui/information_dialogs/AccountInformation.cpp \
			gui/data_input/EditAccount.cpp \
            utility/filesystem.cpp \
            utility/stream_operations.cpp \
            utility/time_class.cpp \
            data/account.cpp \
			gui/data_input/NewTransaction.cpp \
			utility/file_loader.cpp \
			gui/data_input/MoneyTransfer.cpp

HEADERS  += data/global.hpp \
			gui/MainWindow.hpp \
            gui/main_widgets/ManageAccounts.hpp \
            gui/information_dialogs/AccountInformation.hpp \
			gui/data_input/EditAccount.hpp \
            utility/filesystem.hpp \
            utility/stream_operations.hpp \
            utility/time_class.hpp \
            data/account.hpp \
			gui/data_input/NewTransaction.hpp \
			utility/file_loader.hpp \
			gui/data_input/MoneyTransfer.hpp

FORMS    += gui/MainWindow.ui \
            gui/main_widgets/ManageAccounts.ui \
            gui/information_dialogs/AccountInformation.ui \
			gui/data_input/EditAccount.ui \
			gui/data_input/NewTransaction.ui \
			gui/data_input/MoneyTransfer.ui

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
