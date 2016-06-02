#include <QWidget>
#include <vector>
#include <QString>
#include <QListWidgetItem>
#include <QMessageBox>
#include <limits>
#include <type_traits>
#include <QFileDialog>
#include <boost/filesystem.hpp>

#include "ManageAccounts.hpp"
#include "data/account.hpp"
#include "data/global.hpp"
#include "ui_ManageAccounts.h"
#include "gui/data_input/EditAccount.hpp"
#include "gui/data_input/NewTransaction.hpp"
#include "gui/information_dialogs/AccountInformation.hpp"
#include "utility/file_loader.hpp"
#include "gui/data_input/MoneyTransfer.hpp"
#include "interface/mysql_account_interface.hpp"


namespace
{
	QString account_display(const data::account_data&);
	std::string fpoint_acc(const std::string&, const unsigned int&);
	


	inline QString account_display(const data::account_data& a)
	{
		using utility::load;

		data::account_data account{load<data::account_data>(a.id)};
		data::value_t total{0};
		
		for(std::vector<data::transaction_data>::const_iterator it{account.transactions.begin()}; it != account.transactions.end(); ++it)
		{
			total += it->value;
		}
		return (QString::fromStdString(fpoint_acc(std::to_string((long double)total / (long double)100), 2)) + 
			QString{":  "} + account.name);
	}

	inline std::string fpoint_acc(const std::string& s, const unsigned int& accuracy)
	{
		std::string temps{s};
		if(temps.find('.') == std::string::npos)
		{
			if(temps.empty()) temps += "0";
			temps += ("." + std::string{(char)accuracy, '0'});
		}
		else if(!temps.empty())
		{
			auto pos = temps.find('.');
			if((temps.size() - 1) < (pos + accuracy)) temps += std::string{(char)((pos + accuracy) - (temps.size() - 1)), '0'};
			if((temps.size() - 1) > (pos + accuracy)) temps.erase((temps.begin() + (pos + accuracy + 1)), temps.end());
		}
		return temps;
	}


}

ManageAccounts::ManageAccounts(QWidget *parent) : 
        QWidget{parent},
        ui{new Ui::ManageAccounts}
{
    this->ui->setupUi(this);

	this->basic_info = utility::load_basic<data::account_data>();

	this->ui->account_list->clear();
	for(unsigned int x{0}; x < this->basic_info.size(); ++x)
	{
		this->ui->account_list->addItem(account_display(this->basic_info[x]));
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
			this->ui->account_list->clear();
			this->basic_info = utility::load_basic<data::account_data>();
			for(std::size_t x{0}; x < this->basic_info.size(); ++x)
			{
				this->ui->account_list->addItem(account_display(this->basic_info[x]));
			}
		}
	}
}

void ManageAccounts::updateButtons()
{
	bool enable{!this->ui->account_list->selectedItems().empty()};

	this->ui->new_transaction_button->setEnabled(enable);
	this->ui->delete_button->setEnabled(enable);
	this->ui->edit_button->setEnabled(enable);
	this->ui->transfer_button->setEnabled(this->basic_info.size() > 1);
}

void ManageAccounts::transfer()
{
	MoneyTransfer t{this, this->basic_info};
	t.setModal(true);
	t.exec();
}

void ManageAccounts::exportToDatabase()
{
	using account_interface::store_account;

	boost::filesystem::path p{QFileDialog::getSaveFileName(global::main_window, "Choose the database name: ", 
		QString::fromStdString(global::root.string()), "SQLite Databases (*.db)").toStdWString()};
	
	if(!p.string().empty())
	{
		for(auto it = this->basic_info.begin(); it != this->basic_info.end(); ++it)
		{
			store_account(utility::load<data::account_data>(it->id), p);
		}
	}
}

