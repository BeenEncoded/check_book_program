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
    explicit EditAccount(data::account_data&, QWidget* = nullptr);
    ~EditAccount();
    
private:
    Ui::EditAccount *ui;
	data::account_data account;

};

#endif