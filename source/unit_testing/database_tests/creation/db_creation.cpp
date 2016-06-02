#ifdef UNIT_TEST_PROG
#include <iostream>
#include <stdexcept>
#include <exception>
#include <QSqlQuery>
#include <QSqlField>
#include <QSqlRecord>
#include <QDate>

#include "db_creation.hpp"
#include "interface/mysql_account_interface.hpp"
#include "utility/database.hpp"
#include "utility/file_loader.hpp"
#include "unit_testing/random_data.hpp"

namespace
{
	constexpr const char* const invalid_chars{"\'\""};

	void create_account_table(utility::database_class&);
	data::account_data read_account(QSqlQuery&);
	data::transaction_data read_transaction(QSqlQuery&);
	void write_account(const data::account_data&, utility::database_class&);
	void delete_account(const utility::ID_T&, utility::database_class&);
	std::string sanitize_input(const std::string&, const std::string&);
	std::string date_string(const QDate&);


	inline std::string date_string(const QDate& date)
	{
		std::string temps{std::to_string(date.year()) + "-"};
		if(date.month() < 10) temps += "0";
		temps += (std::to_string(date.month()) + "-");
		if(date.day() < 10) temps += "0";
		temps += std::to_string(date.day());
		return temps;
	}

	inline void create_account_table(utility::database_class& db)
	{
		db.query("CREATE TABLE IF NOT EXISTS accounts (\
id " + std::string{ account_interface::mysql_type<utility::ID_T>::type } +" PRIMARY KEY AUTOINCREMENT NOT NULL,\n\
name " + std::string{ account_interface::mysql_type<QString>::type } +" NOT NULL DEFAULT \"\"\
)");
		db.query("CREATE TABLE IF NOT EXISTS transactions (\
key INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,\n\
id " + std::string{ account_interface::mysql_type<utility::ID_T>::type } +" NOT NULL DEFAULT 0,\n\
value " + std::string{ account_interface::mysql_type<data::value_t>::type } +" NOT NULL DEFAULT \"\",\n\
date " + std::string{ account_interface::mysql_type<QDate>::type } +" NOT NULL DEFAULT 0,\n\
name " + std::string{ account_interface::mysql_type<QString>::type } +" NOT NULL DEFAULT \"\",\n\
description " + std::string{ account_interface::mysql_type<QString>::type } +" NOT NULL DEFAULT \"\"\
)");
	}

	inline data::account_data read_account(QSqlQuery& q)
	{
		return data::account_data{
			q.record().field("name").value().value<QString>(),
			q.record().field("id").value().value<utility::ID_T>(),
			std::vector<data::transaction_data>{}
		};
	}

	inline data::transaction_data read_transaction(QSqlQuery& q)
	{
		return data::transaction_data{
			q.record().field("value").value().value<data::value_t>(),
			q.record().field("date").value().value<qint64>(),
			q.record().field("name").value().value<QString>(),
			q.record().field("description").value().value<QString>()
		};
	}

	inline void write_account(const data::account_data& account, utility::database_class& database)
	{
		delete_account(account.id, database);
		database.query("INSERT INTO accounts (id, name) VALUES (" +
			std::to_string(account.id) + ", \'" + sanitize_input(account.name.toStdString(), invalid_chars) + "\')");
		std::cout<< "writing "<< account.transactions.size()<< " transactions..."<< std::endl;
		for(std::size_t x{0}; x < account.transactions.size(); ++x)
		{
			database.query("INSERT INTO transactions (id, value, date, name, description) VALUES (" +
				std::to_string(account.id) + ", " +
				std::to_string(account.transactions[x].value) + ", \'" +
				date_string(QDate::fromJulianDay(account.transactions[x].date)) + "\', \"" +
				sanitize_input(account.transactions[x].name.toStdString(), invalid_chars) + "\", \"" +
				sanitize_input(account.transactions[x].description.toStdString(), invalid_chars) + "\")");
		}
	}

	inline void delete_account(const utility::ID_T& id, utility::database_class& database)
	{
		database.query("DELETE FROM accounts WHERE id=" + std::to_string(id));
		database.query("DELETE FROM transactions WHERE id=" + std::to_string(id));
	}

	inline std::string sanitize_input(const std::string& original, const std::string& ichars)
	{
		std::string temps{original};
		for(std::string::iterator it{temps.begin()}; it != temps.end();)
		{
			if(ichars.find(*it) != std::string::npos)
			{
				it = temps.insert(it, *it);
				if(it != temps.end()) ++it;
			}
			if(it != temps.end()) ++it;
		}
		return temps;
	}


}


namespace testing
{


	void create_db()
	{
		using std::cout;
		using std::endl;

		try
		{
			utility::database_class database{"test_database.db", "QSQLITE", "test_connection"};
			create_account_table(database);
			for(unsigned int x{0}; x < 1; ++x)
			{
				write_account(common::random_account(), database);
			}
		}
		catch(const std::runtime_error& error)
		{
			cout<< error.what()<< endl;
		}
	}


}



#endif