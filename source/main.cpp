#include <QApplication>

#include "gui/MainWindow.hpp"

int main(int c, char** v)
{
    QApplication app{c, v};
    MainWindow window;
    window.show();
    
    return app.exec();
}
