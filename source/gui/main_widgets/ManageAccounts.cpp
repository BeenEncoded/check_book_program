#include <QWidget>
#include <vector>
#include <QString>
#include <QListWidgetItem>

#include "ManageAccounts.hpp"
#include "data/account.hpp"
#include "data/global.hpp"
#include "ui_ManageAccounts.h"
#include "gui/data_input/EditAccount.hpp"

ManageAccounts::ManageAccounts(QWidget *parent) : 
        QWidget{parent},
        ui{new Ui::ManageAccounts}
{
    this->ui->setupUi(this);

	this->basic_info = data::file::load_basic();

	this->ui->account_list->clear();
	for(unsigned int x{0}; x < this->basic_info.size(); ++x)
	{
		this->ui->account_list->addItem(this->basic_info[x].name);
	}
}

ManageAccounts::~ManageAccounts()
{
    delete this->ui;
}

void ManageAccounts::accountSelected(QListWidgetItem* item)
{
	global::main_window->setCentralWidget(
		new EditAccount(
			data::file::load_account(
				this->basic_info[this->ui->account_list->row(item)].id), this));
}

void ManageAccounts::editButtonClicked()
{
	if(!this->ui->account_list->selectedItems().empty())
	{
		global::main_window->setCentralWidget(new EditAccount(
			data::file::load_account(this->basic_info[this->ui->account_list->currentRow()].id), this));
	}
}

void ManageAccounts::newAccount()
{
	global::main_window->setCentralWidget(
		new EditAccount(
			data::account_data{"", 0, std::vector<data::transaction_data>{}}, this));
}

