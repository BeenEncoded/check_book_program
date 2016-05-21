#ifndef MONEYTRANSFER_H
#define MONEYTRANSFER_H
#include <QDialog>
#include <QWidget>
#include <vector>

#include "data/account.hpp"


namespace Ui
{
	class MoneyTransfer;
}

class MoneyTransfer : public QDialog
{
	Q_OBJECT

public:
	explicit MoneyTransfer(QWidget*, const std::vector<data::account_data>&);
	~MoneyTransfer();

public slots:
	void accept();
	void fromActivated(int);
	void toActivated(int);

private:
	Ui::MoneyTransfer *ui;
	std::vector<data::account_data> basic_info;
	std::size_t from, to;

	data::transaction_data create_from_transaction() const;
	data::transaction_data create_to_transaction() const;

};


#endif // MONEYTRANSFER_H
