#ifndef MAIN_WIDGETS_MANAGEACCOUNTS_HPP_INCLUDED
#define MAIN_WIDGETS_MANAGEACCOUNTS_HPP_INCLUDED
#include <QWidget>

namespace Ui
{
    class ManageAccounts;
}

class ManageAccounts : public QWidget
{
    Q_OBJECT
    
public:
    explicit ManageAccounts(QWidget* = nullptr);
    ~ManageAccounts();
    
private:
    Ui::ManageAccounts *ui;
};

#endif