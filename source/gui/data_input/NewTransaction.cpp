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
}

NewTransaction::~NewTransaction()
{
	delete this->ui;
}

void NewTransaction::accept()
{
	data::transaction_data t{(int_least32_t)(this->ui->transaction_value->value() * 100), tdata::time_class{tdata::current_time()}, 
		this->ui->transaction_name->text(),
		this->ui->transaction_description->toPlainText()};
}

void NewTransaction::reject()
{
}

