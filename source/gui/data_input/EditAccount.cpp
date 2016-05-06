#include <QWidget>
#include <utility>
#include <QString>
#include <string>
#include <QMessageBox>
#include <vector>
#include <QDate>
#include <algorithm>
#include <iostream>

#include "EditAccount.hpp"
#include "ui_EditAccount.h"
#include "data/account.hpp"
#include "data/global.hpp"
#include "gui/main_widgets/ManageAccounts.hpp"
#include "utility/time_class.hpp"

namespace
{
	QString date_display(const QDate&);
	bool least_to_greatest(const data::transaction_data&, const data::transaction_data&);
	QString transaction_display(const data::transaction_data&);



	inline QString date_display(const QDate& t)
	{
		return QString::fromStdString(std::to_string(t.month()) + "/" + std::to_string(t.day()) + "/" + 
			std::to_string(t.year()));
	}

	inline bool least_to_greatest(const data::transaction_data& t1, const data::transaction_data& t2)
	{
		return (t1.date > t2.date);
	}

	inline QString transaction_display(const data::transaction_data& transaction)
	{
		return (date_display(QDate::fromJulianDay(transaction.date)) +
			QString{ ":  " } + transaction.name);
	}


}

EditAccount::EditAccount(const data::account_data& acc, QWidget *parent) : 
        QWidget{parent},
        ui{new Ui::EditAccount},
		account{acc},
		current{nullptr}
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
	this->clearmod();
	this->ui->account_name->setText(account.name);
	if(!this->account.transactions.empty())
	{
		this->ui->balance->setText(QString::fromStdString(std::to_string((long double)data::calculate_resulting_balances(this->account.transactions)[0] / (long double)100)));
	}
	std::sort(this->account.transactions.begin(), this->account.transactions.end(), least_to_greatest);
	this->ui->transaction_list->clear();
	for(unsigned int x{0}; x < this->account.transactions.size(); ++x)
	{
		this->ui->transaction_list->addItem(transaction_display(this->account.transactions[x]));
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

/**
If a transaction is selected, then it sets up the transaction group box and
if there is no transaction selected, it clears it and disables it.
*/
void EditAccount::updateTransactionModification()
{
	if(this->tmodified())
	{
		auto answer = QMessageBox::question(this, "Are you sure?", "You've modified a transaction, do \
you really want to discard the changes?");

		if(answer == QMessageBox::No) return;
	}
	if(!this->ui->transaction_list->selectedItems().empty())
	{
		this->settmod(this->account.transactions[this->ui->transaction_list->currentRow()]);
	}
	else this->clearmod();
}

/**
Enables the transaction modification group box and sets the values of
the input widgets accordingly.  Also enabled the apply_transaction_button.
*/
void EditAccount::settmod(data::transaction_data& transaction)
{
	this->current = &transaction;

	this->ui->transaction_box->setEnabled(true);
	this->ui->transaction_name->setText(transaction.name);
	this->ui->transaction_date->setDate(QDate::fromJulianDay(transaction.date));
	this->ui->transaction_value->setValue((double)transaction.value / (double)100);
	this->ui->transaction_description->setPlainText(transaction.description);
	this->ui->apply_transaction_button->setEnabled(false);
}

void EditAccount::clearmod()
{
	this->current = nullptr;
	this->ui->transaction_name->setText("");
	this->ui->transaction_date->setDate(QDate::currentDate());
	this->ui->transaction_value->setValue(0);
	this->ui->transaction_description->setPlainText("");
	this->ui->transaction_box->setEnabled(false);
}

bool EditAccount::tmodified()
{
	if(!this->ui->transaction_box->isEnabled() || (this->current == nullptr)) return false;
	return (this->ui->transaction_name->isModified() || 
		((int_least32_t)(this->ui->transaction_value->value() * 100) != this->current->value)  ||
		(this->ui->transaction_date->date() != QDate::fromJulianDay(this->current->date))  ||
		(this->ui->transaction_description->toPlainText() != this->current->description));
}

void EditAccount::updateTransactionApplyButton()
{
	this->ui->apply_transaction_button->setEnabled(this->tmodified());
}

void EditAccount::applyTransaction()
{
	this->current->value = (this->ui->transaction_value->value() * 100);
	this->current->name = this->ui->transaction_name->text();
	this->current->description = this->ui->transaction_description->toPlainText();
	this->current->date = this->ui->transaction_date->date().toJulianDay();
	
	//set the transaction to "not modified"
	this->ui->transaction_name->setModified(false);

	//some information updates for the user:
	this->ui->balance->setText(QString::fromStdString(
		std::to_string(
		((long double)data::calculate_resulting_balances(this->account.transactions)[0] / (long double)100))));
	std::sort(this->account.transactions.begin(), this->account.transactions.end(), least_to_greatest);
	this->ui->transaction_list->clear();
	for(unsigned int x{0}; x < this->account.transactions.size(); ++x)
	{
		this->ui->transaction_list->addItem(transaction_display(this->account.transactions[x]));
	}

	//everything else's value is compared directly...
	this->updateTransactionApplyButton();
	this->clearmod();
}

