#include <string>
#include <QSqlRecord>
#include <QSqlField>
#include <QString>
#include <boost/filesystem.hpp>

#include "mysql_account_interface.hpp"
#include "data/account.hpp"
#include "utility/database.hpp"
#include "data/global.hpp"


namespace
{
	constexpr const char* const invalid_chars{ "\'\"" };

	template<typename type> struct mysql_type;


	/* Some template meta programming to help with typing
	SQL types: */
	template<typename t>
	struct mysql_type
	{
		static constexpr const char* const type{ nullptr };
	};

	template<>
	struct mysql_type<data::value_t>
	{
		static constexpr const char* const type{ "BIGINT(64)" };
	};

	template<>
	struct mysql_type<QString>
	{
		static constexpr const char* const type{ "MEDIUMTEXT(500)" };
	};

	template<>
	struct mysql_type<utility::ID_T>
	{
		static constexpr const char* const type{ "INTEGER" };
	};

	template<>
	struct mysql_type<QDate>
	{
		static constexpr const char* const type{ "DATE" };
	};

	void create_account_table(utility::database_class&);
	void write_account(const data::account_data&, utility::database_class&);
	void delete_account(const utility::ID_T&, utility::database_class&);
	std::string sanitize_input(const std::string&, const std::string&);
	std::string date_string(const QDate&);


	inline std::string date_string(const QDate& date)
	{
		std::string temps{ std::to_string(date.year()) + "-" };
		if (date.month() < 10) temps += "0";
		temps += (std::to_string(date.month()) + "-");
		if (date.day() < 10) temps += "0";
		temps += std::to_string(date.day());
		return temps;
	}

	inline void create_account_table(utility::database_class& db)
	{
		db.query("CREATE TABLE IF NOT EXISTS accounts (\
id " + std::string{mysql_type<utility::ID_T>::type } +" PRIMARY KEY AUTOINCREMENT NOT NULL,\n\
name " + std::string{mysql_type<QString>::type } +" NOT NULL DEFAULT \"\"\
)");
		db.query("CREATE TABLE IF NOT EXISTS transactions (\
key INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,\n\
id " + std::string{mysql_type<utility::ID_T>::type } +" NOT NULL DEFAULT 0,\n\
value " + std::string{mysql_type<data::value_t>::type } +" NOT NULL DEFAULT \"\",\n\
date " + std::string{mysql_type<QDate>::type } +" NOT NULL DEFAULT 0,\n\
name " + std::string{mysql_type<QString>::type } +" NOT NULL DEFAULT \"\",\n\
description " + std::string{mysql_type<QString>::type } +" NOT NULL DEFAULT \"\"\
)");
	}

	inline void write_account(const data::account_data& account, utility::database_class& database)
	{
		delete_account(account.id, database);
		database.query("INSERT INTO accounts (id, name) VALUES (" +
			std::to_string(account.id) + ", \'" + sanitize_input(account.name.toStdString(), invalid_chars) + "\')");
		for (std::size_t x{ 0 }; x < account.transactions.size(); ++x)
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
		std::string temps{ original };
		for (std::string::iterator it{ temps.begin() }; it != temps.end();)
		{
			if (ichars.find(*it) != std::string::npos)
			{
				it = temps.insert(it, *it);
				if (it != temps.end()) ++it;
			}
			if (it != temps.end()) ++it;
		}
		if(temps.size() > 500) temps.erase((temps.begin() + 500), temps.end());
		return temps;
	}


}

namespace account_interface
{
	void store_account(const data::account_data& account, const boost::filesystem::path& p)
	{
		using boost::filesystem::path;

		utility::database_class database{p, "QSQLITE", "sqlite_db_connection"};
		create_account_table(database);
		write_account(account, database);
	}


}

