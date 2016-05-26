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

SOURCES += source/main.cpp \
			source/data/global.cpp \
            source/gui/MainWindow.cpp \
            source/gui/main_widgets/ManageAccounts.cpp \
            source/gui/information_dialogs/AccountInformation.cpp \
			source/gui/data_input/EditAccount.cpp \
            source/utility/filesystem.cpp \
            source/utility/stream_operations.cpp \
            source/utility/time_class.cpp \
            source/data/account.cpp \
			source/gui/data_input/NewTransaction.cpp \
			source/utility/file_loader.cpp \
			source/gui/data_input/MoneyTransfer.cpp

HEADERS  += source/data/global.hpp \
			source/gui/MainWindow.hpp \
            source/gui/main_widgets/ManageAccounts.hpp \
            source/gui/information_dialogs/AccountInformation.hpp \
			source/gui/data_input/EditAccount.hpp \
            source/utility/filesystem.hpp \
            source/utility/stream_operations.hpp \
            source/utility/time_class.hpp \
            source/data/account.hpp \
			source/gui/data_input/NewTransaction.hpp \
			source/utility/file_loader.hpp \
			source/gui/data_input/MoneyTransfer.hpp

FORMS    += source/gui/MainWindow.ui \
            source/gui/main_widgets/ManageAccounts.ui \
            source/gui/information_dialogs/AccountInformation.ui \
			source/gui/data_input/EditAccount.ui \
			source/gui/data_input/NewTransaction.ui \
			source/gui/data_input/MoneyTransfer.ui

#RESOURCES += 

CONFIG(debug, debug|release) {
    message(DEBUG BUILD)
    DESTDIR = build/debug
}

CONFIG(release, debug|release) {
    message(RELEASE BUILD)
    DESTDIR = build/release
}

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui
