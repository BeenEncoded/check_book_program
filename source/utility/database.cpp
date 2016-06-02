#include <boost/filesystem.hpp>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <stdexcept>
#include <exception>
#include <string>

#include "database.hpp"

utility::database_class::database_class(const boost::filesystem::path& file, 
	const std::string& driver, 
	const std::string& cname) : 
		db{QSqlDatabase::addDatabase(QString::fromStdString(driver), QString::fromStdString(cname))}
{
	this->db.setHostName("localhost");
	this->db.setDatabaseName(QString::fromStdString(file.string()));
	this->db.open("", "");
}

utility::database_class::~database_class()
{
	this->db.close();
	QSqlDatabase::removeDatabase(this->db.connectionName());
}

QSqlQuery utility::database_class::query(const std::string& q)
{
	QSqlQuery query{this->db.exec(QString::fromStdString(q))};
	query.finish();
	if(this->db.lastError().type() != QSqlError::NoError)
	{
		throw std::runtime_error{this->db.lastError().text().toStdString()};
	}
	return query;
}

