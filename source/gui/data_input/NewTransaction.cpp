#include <QWidget>
#include <QDialog>

#include "NewTransaction.hpp"
#include "ui_NewTransaction.h"
#include "utility/time_class.hpp"
#include "data/account.hpp"

NewTransaction::NewTransaction(const data::account_data& a, QWidget* parent) :
	QDialog{parent},
	ui{new Ui::NewTransaction},
	account{a}
{
	this->ui->setupUi(this);
	this->ui->transaction_date->setDate(QDate::currentDate());
}

NewTransaction::~NewTransaction()
{
	delete this->ui;
}

void NewTransaction::accept()
{
	this->account.transactions.insert(this->account.transactions.begin(), data::transaction_data{
		(int_least32_t)(this->ui->transaction_value->value() * 100), 
		this->ui->transaction_date->date().toJulianDay(),
		this->ui->transaction_name->text(),
		this->ui->transaction_description->toPlainText()});
	data::file::save(this->account);
	QDialog::accept();
}

