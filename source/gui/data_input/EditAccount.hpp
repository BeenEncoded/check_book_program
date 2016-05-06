#ifndef DATA_INPUT_EDITACCOUNT_HPP_INCLUDED
#define DATA_INPUT_EDITACCOUNT_HPP_INCLUDED
#include <QWidget>

#include "data/account.hpp"

namespace Ui
{
    class EditAccount;
}

class EditAccount : public QWidget
{
    Q_OBJECT
    
public:
    explicit EditAccount(const data::account_data&, QWidget* = nullptr);
    ~EditAccount();

public slots:
	void closeMenu();
	void cancelClicked();
	void doneClicked();
	void updateTransactionModification();
	void updateTransactionApplyButton();
	void applyTransaction();
    
private:
    Ui::EditAccount *ui;
	data::account_data account;
	data::transaction_data* current;

	void set_to(data::account_data&);
	void save();
	void settmod(data::transaction_data&);
	void clearmod();
	bool tmodified();

};

#endif