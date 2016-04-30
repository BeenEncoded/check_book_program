

#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "gui/main_widgets/ManageAccounts.hpp"
#include "data/global.hpp"

MainWindow::MainWindow(QWidget *parent) : 
        QMainWindow{parent},
        ui{new Ui::MainWindow}
{
    this->ui->setupUi(this);
	global::main_window = this;
    this->setCentralWidget(new ManageAccounts{this});
}

MainWindow::~MainWindow()
{
    delete this->ui;
}

