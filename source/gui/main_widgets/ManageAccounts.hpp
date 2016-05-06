#ifndef MAIN_WIDGETS_MANAGEACCOUNTS_HPP_INCLUDED
#define MAIN_WIDGETS_MANAGEACCOUNTS_HPP_INCLUDED
#include <QWidget>
#include <QListWidgetItem>
#include <vector>

#include "data/account.hpp"

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

public slots:
	void accountSelected(QListWidgetItem*);
	void editButtonClicked();
	void newAccount();
	void deleteAccount();
	void newTransaction();
	void updateButtons();
    
private:
    Ui::ManageAccounts *ui;
	std::vector<data::account_data> basic_info;
};

#endif