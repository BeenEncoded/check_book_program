#ifndef MAIN_WIDGETS_MANAGEACCOUNTS_HPP_INCLUDED
#define MAIN_WIDGETS_MANAGEACCOUNTS_HPP_INCLUDED
#include <QWidget>
#include <QListWidgetItem>
#include <vector>
#include <QMenu>
#include <utility>
#include <QPrinter>

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
	void transfer();
	void exportToDatabase();
	void printSummary();
	void printSummaryToPrinter(QPrinter*);
    
private:
    Ui::ManageAccounts *ui;
	std::vector<data::account_data> basic_info;
	std::shared_ptr<QMenu> menu;

	std::string account_summary();

};

#endif