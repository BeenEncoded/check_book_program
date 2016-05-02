#ifndef DATA_INPUT_NEWTRANSACTION_HPP_INCLUDED
#define DATA_INPUT_NEWTRANSACTION_HPP_INCLUDED
#include <QDialog>
#include <QWidget>

#include "data/account.hpp"

namespace Ui
{
	class NewTransaction;
}

class NewTransaction : public QDialog
{
	Q_OBJECT
	
public:
	explicit NewTransaction(const data::account_data&, QWidget* = nullptr);
	~NewTransaction();

public slots:
	void accept();
	void reject();

private:
	Ui::NewTransaction *ui;
	data::account_data account;

};

#endif