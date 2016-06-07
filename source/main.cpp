#ifndef UNIT_TEST_PROG
#include <QApplication>

#include "gui/MainWindow.hpp"

int main(int c, char** v)
{
    QApplication app{c, v};
    MainWindow window;
    window.show();
    
    return app.exec();
}
#else
#include <QCoreApplication>
#include <thread>

#include "unit_testing/test.hpp"

int main(int c, char** v)
{
	QCoreApplication prog{c, v};
	std::thread execution{test};
	auto result = prog.exec();
	execution.join();
	return result;
}
#endif
