#include <QWidget>
#include <vector>
#include <QString>
#include <QListWidgetItem>
#include <QMessageBox>

#include "ManageAccounts.hpp"
#include "data/account.hpp"
#include "data/global.hpp"
#include "ui_ManageAccounts.h"
#include "gui/data_input/EditAccount.hpp"
#include "gui/data_input/NewTransaction.hpp"
#include "gui/information_dialogs/AccountInformation.hpp"
#include "utility/file_loader.hpp"

ManageAccounts::ManageAccounts(QWidget *parent) : 
        QWidget{parent},
        ui{new Ui::ManageAccounts}
{
    this->ui->setupUi(this);

	this->basic_info = utility::load_basic<data::account_data>();

	this->ui->account_list->clear();
	for(unsigned int x{0}; x < this->basic_info.size(); ++x)
	{
		this->ui->account_list->addItem(this->basic_info[x].name);
	}
	this->updateButtons();
	global::main_window->setWindowTitle("Manage Accounts");
}

ManageAccounts::~ManageAccounts()
{
    delete this->ui;
}

void ManageAccounts::accountSelected(QListWidgetItem* item)
{
	AccountInformation dialog{global::main_window, 
		utility::load<data::account_data>(this->basic_info[this->ui->account_list->row(item)].id)};
	dialog.setModal(true);
	dialog.exec();
}

void ManageAccounts::editButtonClicked()
{
	if(!this->ui->account_list->selectedItems().empty())
	{
		global::main_window->setCentralWidget(new EditAccount(
			utility::load<data::account_data>(this->basic_info[this->ui->account_list->currentRow()].id), global::main_window));
	}
}

void ManageAccounts::newAccount()
{
	global::main_window->setCentralWidget(
		new EditAccount(
			data::account_data{"", 0, std::vector<data::transaction_data>{}}, global::main_window));
}

void ManageAccounts::deleteAccount()
{
	if(!this->ui->account_list->selectedItems().empty())
	{
		auto index = this->ui->account_list->currentRow();
		auto answer = QMessageBox::question(this, "Are you sure??", QString::fromStdWString(L"Do you really want to delete \"" + 
			this->basic_info[index].name.toStdWString() + L"\"??  This is permanent!"));
		if(answer == QMessageBox::Yes)
		{
			utility::remove<data::account_data>(this->basic_info[index].id);
			this->basic_info.erase(this->basic_info.begin() + index);

			this->ui->account_list->clear();
			for(unsigned int x{0}; x < this->basic_info.size(); ++x)
			{
				this->ui->account_list->addItem(this->basic_info[x].name);
			}
			this->updateButtons();
		}
	}
}

void ManageAccounts::newTransaction()
{
	if(!this->ui->account_list->selectedItems().empty())
	{
		auto index = this->ui->account_list->currentRow();
		if((index >= 0) && (index <  this->basic_info.size()))
		{
			data::account_data account{utility::load<data::account_data>(this->basic_info[index].id)};
			NewTransaction d{account, this};
			d.setModal(true);
			d.exec();
		}
	}
}

void ManageAccounts::updateButtons()
{
	bool enable{!this->ui->account_list->selectedItems().empty()};

	this->ui->new_transaction_button->setEnabled(enable);
	this->ui->delete_button->setEnabled(enable);
	this->ui->edit_button->setEnabled(enable);
}

