#ifndef INFO_DIAGS_ACCOUNTINFORMATION_HPP_INCLUDED
#define INFO_DIAGS_ACCOUNTINFORMATION_HPP_INCLUDED
#include <QDialog>
#include <QWidget>

namespace Ui
{
    class AccountInformation;
}

class AccountInformation : public QDialog
{
    Q_OBJECT
    
public:
    explicit AccountInformation(QWidget* = nullptr);
    ~AccountInformation();
    
private:
    Ui::AccountInformation *ui;
};

#endif