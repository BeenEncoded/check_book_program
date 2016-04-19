#include <QWidget>

#include "ui_ManageAccounts.h"
#include "ManageAccounts.hpp"

ManageAccounts::ManageAccounts(QWidget *parent) : 
        QWidget{parent},
        ui{new Ui::ManageAccounts}
{
    this->ui->setupUi(this);
}

ManageAccounts::~ManageAccounts()
{
    delete this->ui;
}