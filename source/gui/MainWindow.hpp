#ifndef GUI_MAINWINDOW_HPP_INCLUDED
#define GUI_MAINWINDOW_HPP_INCLUDED
#include <QWidget>
#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget* = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
};

#endif