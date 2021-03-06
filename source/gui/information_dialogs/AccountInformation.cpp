#include <QDialog>
#include <QWidget>
#include <QString>
#include <string>
#include <QDate>
#include <QTreeWidgetItem>
#include <algorithm>
#include <exception>
#include <stdexcept>

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
		account{a},
		items{}
{
    this->ui->setupUi(this);
	this->set_account(this->account);
	this->ui->list->setHeaderLabels({ "Date", "Name", "Value", "Balance" });
}

AccountInformation::~AccountInformation()
{
    delete this->ui;
}

void AccountInformation::set_account(const data::account_data& a)
{
	this->cleart();
	this->update_list();
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

void AccountInformation::update_list()
{
	std::sort(this->account.transactions.begin(), this->account.transactions.end(), trans_comp);
	this->ui->list->clear();
	this->items.erase(this->items.begin(), this->items.end());
	for(std::size_t x{0}; x < this->account.transactions.size(); ++x)
	{
		QTreeWidgetItem *item{new QTreeWidgetItem{{
				date_display(QDate::fromJulianDay(this->account.transactions[x].date)),
				this->account.transactions[x].name,
				QString::fromStdString(fpoint_acc(std::to_string((long double)this->account.transactions[x].value / 100), 2)),
				QString::fromStdString(fpoint_acc(std::to_string((long double)data::calculate_resulting_balances(this->account.transactions)[x] / 100), 2))}}};
		this->ui->list->addTopLevelItem(item);
		this->items.push_back(item);
	}
}

std::size_t AccountInformation::index(QTreeWidgetItem* item)
{
	for(std::size_t x{0}; x < this->items.size(); ++x)
	{
		if(this->items[x] == item) return x;
	}
	throw std::runtime_error{"Error: invalid item!"};
}

void AccountInformation::updateTransactionInformation(QTreeWidgetItem* item)
{
	if(!this->ui->list->selectedItems().empty())
	{
		this->set_transaction(this->account.transactions[this->index(item)]);
	}
	else this->cleart();
}

