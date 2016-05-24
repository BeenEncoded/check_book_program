#include <QDialog>
#include <QWidget>
#include <QString>
#include <string>
#include <QDate>
#include <QListWidgetItem>
#include <algorithm>

#include "AccountInformation.hpp"
#include "ui_AccountInformation.h"
#include "data/account.hpp"

namespace
{
	QString transaction_display(const data::transaction_data&);
	QString date_display(const QDate&);
	bool trans_comp(const data::transaction_data&, const data::transaction_data&);
	std::string fpoint_acc(const std::string&, const unsigned int&);


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

	inline bool trans_comp(const data::transaction_data& t1, const data::transaction_data& t2)
	{
		return (t1.date > t2.date);
	}

	inline std::string fpoint_acc(const std::string& s, const unsigned int& accuracy)
	{
		std::string temps{ s };
		if (temps.find('.') == std::string::npos)
		{
			if (temps.empty()) temps += "0";
			temps += ("." + std::string{ (char)accuracy, '0' });
		}
		else if (!temps.empty())
		{
			auto pos = temps.find('.');
			if ((temps.size() - 1) < (pos + accuracy)) temps += std::string{ (char)((pos + accuracy) - (temps.size() - 1)), '0' };
			if ((temps.size() - 1) > (pos + accuracy)) temps.erase((temps.begin() + (pos + accuracy + 1)), temps.end());
		}
		return temps;
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
	this->ui->list->clear();
	std::sort(this->account.transactions.begin(), this->account.transactions.end(), trans_comp);
	for(unsigned int x{0}; x < this->account.transactions.size(); ++x)
	{
		this->ui->list->addItem(transaction_display(this->account.transactions[x]));
	}
	this->ui->account_name->setText(a.name);
	data::value_t total{0};
	for(std::vector<data::transaction_data>::const_iterator it{this->account.transactions.begin()}; it != this->account.transactions.end(); ++it)
	{
		total += it->value;
	}
	this->ui->balance->setText(QString::fromStdString(fpoint_acc(std::to_string(((long double)total / (long double)100)), 2)));
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
	this->ui->transaction_amount->setText(QString::fromStdString(fpoint_acc(std::to_string(((long double)transaction.value / (long double)100)), 2)));
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

