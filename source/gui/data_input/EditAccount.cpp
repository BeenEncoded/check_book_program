#include <QWidget>

#include "EditAccount.hpp"
#include "ui_EditAccount.h"

EditAccount::EditAccount(QWidget *parent) : 
        QWidget{parent},
        ui{new Ui::EditAccount}
{
    this->ui->setupUi(this);
}

EditAccount::~EditAccount()
{
    delete this->ui;
}

