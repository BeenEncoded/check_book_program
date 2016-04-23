#include <QDialog>

#include <QWidget>

#include "AccountInformation.hpp"
#include "ui_AccountInformation.h"

AccountInformation::AccountInformation(QWidget *parent) : 
        QDialog{parent},
        ui{new Ui::AccountInformation}
{
    this->ui->setupUi(this);
}

AccountInformation::~AccountInformation()
{
    delete this->ui;
}