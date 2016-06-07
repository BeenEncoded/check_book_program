#ifndef DATABASE_HPP_INCLUDED
#define DATABASE_HPP_INCLUDED
#include <QString>
#include <QSqlDatabase>
#include <string>
#include <QSqlQuery>
#include <boost/filesystem.hpp>

namespace utility
{
	class database_class;


	class database_class
	{
	public:
		database_class(const database_class&) = delete;
		database_class(database_class&&) = delete;
		explicit database_class(const boost::filesystem::path&, const std::string&, const std::string&);
		~database_class();

		database_class& operator=(const database_class&) = delete;
		database_class& operator=(database_class&&) = delete;

		QSqlQuery query(const std::string&);

	private:
		QSqlDatabase db;

	};
}

#endif