#include <QWidget>
#include <vector>
#include <QVariant>
#include <QDate>
#include <QMessageBox>
#include <string>

#include "MoneyTransfer.hpp"
#include "ui_MoneyTransfer.h"
#include "data/account.hpp"
#include "utility/file_loader.hpp"

MoneyTransfer::MoneyTransfer(QWidget* parent, const std::vector<data::account_data>& b) : 
	QDialog{parent},
	ui{new Ui::MoneyTransfer},
	basic_info{b},
	from{(std::size_t)-1},
	to{(std::size_t)-1}
{
	this->ui->setupUi(this);
	for(unsigned int x{0}; x < this->basic_info.size(); ++x)
	{
		this->ui->from_list->addItem(this->basic_info[x].name, QVariant{(int)x});
	}
	this->fromActivated(0);
	this->toActivated(0);
	this->ui->date->setDate(QDate::currentDate());
}

MoneyTransfer::~MoneyTransfer()
{
	delete this->ui;
}

void MoneyTransfer::accept()
{
	using utility::load;
	using utility::save;

	data::account_data account{load<data::account_data>(this->basic_info[this->from].id)};
	account.transactions.insert(account.transactions.begin(), this->create_from_transaction());
	save(account);
	account = load<data::account_data>(this->basic_info[this->to].id);
	account.transactions.insert(account.transactions.begin(), this->create_to_transaction());
	save(account);
	QDialog::accept();
}

void MoneyTransfer::fromActivated(int)
{
	if(this->ui->from_list->currentIndex() > -1)
	{
		this->from = (std::size_t)this->ui->from_list->currentData().toInt();
		this->ui->to_list->clear();
		for(std::size_t x{0}; x < this->basic_info.size(); ++x)
		{
			if(x != this->from)
			{
				this->ui->to_list->addItem(this->basic_info[x].name, QVariant{(int)x});
			}
		}
		this->toActivated(0);
	}
	else
	{
		this->from = (std::size_t)-1;
		this->ui->to_list->clear();
		this->ui->execute_button->setEnabled(false);
	}
}

void MoneyTransfer::toActivated(int)
{
	if(this->ui->to_list->currentIndex() > -1)
	{
		this->to = (std::size_t)this->ui->to_list->currentData().toInt();
		this->ui->execute_button->setEnabled(true);
	}
	else
	{
		this->to = (std::size_t)-1;
		this->ui->execute_button->setEnabled(false);
	}
}

data::transaction_data MoneyTransfer::create_from_transaction() const
{
	data::transaction_data transaction;
	transaction.name = (QString{"Transfer to \""} + this->basic_info[this->to].name +
		QString{"\""});
	transaction.value = (this->ui->value->value() * (long double)(-100));
	transaction.description = this->ui->description->toPlainText();
	transaction.date = this->ui->date->date().toJulianDay();
	return transaction;
}

data::transaction_data MoneyTransfer::create_to_transaction() const
{
	data::transaction_data transaction;
	transaction.name = (QString{ "Transfer from \"" } +this->basic_info[this->from].name +
		QString{ "\"" });
	transaction.value = (this->ui->value->value() * (long double)(100));
	transaction.description = this->ui->description->toPlainText();
	transaction.date = this->ui->date->date().toJulianDay();
	return transaction;
}

