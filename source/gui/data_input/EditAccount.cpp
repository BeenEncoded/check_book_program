#include <QWidget>
#include <utility>
#include <QString>
#include <string>
#include <QMessageBox>
#include <vector>

#include "EditAccount.hpp"
#include "ui_EditAccount.h"
#include "data/account.hpp"
#include "data/global.hpp"
#include "gui/main_widgets/ManageAccounts.hpp"
#include "utility/time_class.hpp"

namespace
{
	QString date_display(const tdata::time_class&);



	inline QString date_display(const tdata::time_class& t)
	{
		return QString::fromStdString(std::to_string(t.month()) + "/" + std::to_string(t.mday()) + "/" + 
			std::to_string(t.gyear()));
	}




}

EditAccount::EditAccount(const data::account_data& acc, QWidget *parent) : 
        QWidget{parent},
        ui{new Ui::EditAccount},
		account{acc}
{
    this->ui->setupUi(this);
	this->set_to(this->account);
}

EditAccount::~EditAccount()
{
    delete this->ui;
}

void EditAccount::closeMenu()
{
	global::main_window->setCentralWidget(new ManageAccounts(global::main_window));
}

void EditAccount::save()
{
	this->account.name = this->ui->account_name->text();
	data::file::save(this->account);
}

void EditAccount::set_to(data::account_data& account)
{
	this->ui->account_name->setText(account.name);
	if(!this->account.transactions.empty()) this->ui->balance->setText(QString::fromStdString(std::to_string(data::calculate_resulting_balances(this->account.transactions)[0])));
	this->ui->transaction_list->clear();
	for(unsigned int x{0}; x < account.transactions.size(); ++x)
	{
		this->ui->transaction_list->addItem(date_display(account.transactions[x].date) + 
			QString{":  "} + account.transactions[x].name);
	}
}

void EditAccount::cancelClicked()
{
	auto answer = QMessageBox::question(this, "Are you sure?", (QString{"Do you really want to discard changes made to \""} + 
		this->ui->account_name->text() + QString{"\"?"}));

	if(answer == QMessageBox::Yes)
	{
		this->closeMenu();
	}
}

void EditAccount::doneClicked()
{
	this->save();
	this->closeMenu();
}

