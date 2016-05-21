#ifndef INFO_DIAGS_ACCOUNTINFORMATION_HPP_INCLUDED
#define INFO_DIAGS_ACCOUNTINFORMATION_HPP_INCLUDED
#include <QDialog>
#include <QWidget>
#include <QListWidgetItem>

#include "data/account.hpp"

namespace Ui
{
    class AccountInformation;
}

class AccountInformation : public QDialog
{
    Q_OBJECT
    
public:
    explicit AccountInformation(QWidget*, const data::account_data&);
    ~AccountInformation();

public slots:
	void updateTransactionInformation(QListWidgetItem*);
    
private:
    Ui::AccountInformation *ui;
	data::account_data account;

	void set_account(const data::account_data&);
	void cleart();
	void set_transaction(const data::transaction_data&);
};

#endif