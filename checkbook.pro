QT  += core gui widgets sql

CONFIG += C++14 debug_build

QMAKE_CXXFLAGS += /IC:\Users\include #additional includes

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = checkbook_program
TEMPLATE = app

include(files.pri)

debug_build {
    message(DEBUG BUILD)
    DESTDIR = build/debug

	LIBS += "C:\lib\x64\libboost_system-vc140-mt-gd-1_60.lib" \
			"C:\lib\x64\libboost_filesystem-vc140-mt-gd-1_60.lib" \
			"C:\lib\x64\libboost_regex-vc140-mt-gd-1_60.lib"
}

release_build {
    message(RELEASE BUILD)
    DESTDIR = build/release

	LIBS += "C:\lib\x64\libboost_system-vc140-mt-1_60.lib" \
			"C:\lib\x64\libboost_filesystem-vc140-mt-1_60.lib" \
			"C:\lib\x64\libboost_regex-vc140-mt-1_60.lib"
}

test_build {
	CONFIG += console
	message(TESTING BUILD)
    DESTDIR = build/testing

	include(test_files.pri)
	LIBS += "C:\lib\x64\libboost_system-vc140-mt-gd-1_60.lib" \
			"C:\lib\x64\libboost_filesystem-vc140-mt-gd-1_60.lib" \
			"C:\lib\x64\libboost_regex-vc140-mt-gd-1_60.lib" \
			"C:\lib\x64\UnitTest++.lib"

	DEFINES += UNIT_TEST_PROG
}

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui
