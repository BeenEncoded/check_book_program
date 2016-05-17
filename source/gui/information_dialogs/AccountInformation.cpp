#include <QDialog>
#include <QWidget>
#include <QString>
#include <string>
#include <QDate>
#include <QListWidgetItem>

#include "AccountInformation.hpp"
#include "ui_AccountInformation.h"
#include "data/account.hpp"

namespace
{
	QString transaction_display(const data::transaction_data&);
	QString date_display(const QDate&);


	inline QString date_display(const QDate& date)
	{
		return (QString::fromStdString(std::to_string(date.month())) + QString{"/"} + 
			QString::fromStdString(std::to_string(date.day())) + QString{"/"} + 
			QString::fromStdString(std::to_string(date.year())));
	}

	inline QString transaction_display(const data::transaction_data& t)
	{
		return (QString{"["} + date_display(QDate::fromJulianDay(t.date)) + QString{"]:  "} + 
			t.name);
	}


}

AccountInformation::AccountInformation(QWidget* parent, const data::account_data& a) : 
        QDialog{parent},
        ui{new Ui::AccountInformation},
		account{a}
{
    this->ui->setupUi(this);
	this->set_account(this->account);
}

AccountInformation::~AccountInformation()
{
    delete this->ui;
}

void AccountInformation::set_account(const data::account_data& a)
{
	this->cleart();
	for(unsigned int x{0}; x < this->account.transactions.size(); ++x)
	{
		this->ui->list->addItem(transaction_display(this->account.transactions[x]));
	}
	this->ui->account_name->setText(a.name);
	int_least32_t total{0};
	for(std::vector<data::transaction_data>::const_iterator it{this->account.transactions.begin()}; it != this->account.transactions.end(); ++it)
	{
		total += it->value;
	}
	this->ui->balance->setText(QString::fromStdString(std::to_string(((long double)total / (long double)100))));
}

/*
Clears the transaction information box.
*/
void AccountInformation::cleart()
{
	this->ui->transaction_information_box->setEnabled(false);
	this->ui->transaction_name->setText("");
	this->ui->transaction_date->setText(date_display(QDate::currentDate()));
	this->ui->transaction_amount->setText("0.00");
	this->ui->transaction_description->setPlainText("");
}

/*
Sets the account information box to the transaction passed.
*/
void AccountInformation::set_transaction(const data::transaction_data& transaction)
{
	this->ui->transaction_information_box->setEnabled(true);
	this->ui->transaction_name->setText(transaction.name);
	this->ui->transaction_date->setText(date_display(QDate::fromJulianDay(transaction.date)));
	this->ui->transaction_amount->setText(QString::fromStdString(std::to_string(((long double)transaction.value / (long double)100))));
	this->ui->transaction_description->setPlainText(transaction.description);
}

void AccountInformation::updateTransactionInformation(QListWidgetItem* i)
{
	if(!this->ui->list->selectedItems().empty())
	{
		this->set_transaction(this->account.transactions[this->ui->list->row(i)]);
	}
	else this->cleart();
}

