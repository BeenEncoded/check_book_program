#ifndef DATA_INPUT_EDITACCOUNT_HPP_INCLUDED
#define DATA_INPUT_EDITACCOUNT_HPP_INCLUDED
#include <QWidget>

namespace Ui
{
    class EditAccount;
}

class EditAccount : public QWidget
{
    Q_OBJECT
    
public:
    explicit EditAccount(QWidget* = nullptr);
    ~EditAccount();
    
private:
    Ui::EditAccount *ui;
};

#endif