#ifndef DATA_INPUT_EDITACCOUNT_HPP_INCLUDED
#define DATA_INPUT_EDITACCOUNT_HPP_INCLUDED
#include <QWidget>
#include <vector>

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

	//transaction modification
	void updateTransactionModification();
	void updateTransactionApplyButton();
	void applyTransaction();
	void deleteTransaction();
    
private:
    Ui::EditAccount *ui;
	data::account_data account;
	std::size_t current;

	void set_to(data::account_data&);
	void save();
	void settmod(const std::size_t&);
	void clearmod();
	bool tmodified();

};

#endif