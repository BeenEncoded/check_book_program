#include <QWidget>
#include <utility>

#include "EditAccount.hpp"
#include "ui_EditAccount.h"
#include "data/account.hpp"
#include "data/global.hpp"
#include "gui/main_widgets/ManageAccounts.hpp"

EditAccount::EditAccount(data::account_data& acc, QWidget *parent) : 
        QWidget{parent},
        ui{new Ui::EditAccount},
		account{std::move(acc)}
{
    this->ui->setupUi(this);
}

EditAccount::~EditAccount()
{
    delete this->ui;
}

void EditAccount::closeMenu()
{
	global::main_window->setCentralWidget(new ManageAccounts(global::main_window));
}

