#ifndef MYSQL_ACCOUNT_INTERFACE_HPP_INCLUDED
#define MYSQL_ACCOUNT_INTERFACE_HPP_INCLUDED
#include <string>
#include <QDate>
#include <QString>
#include <boost/filesystem.hpp>

#include "data/account.hpp"
#include "utility/file_loader.hpp"

namespace account_interface
{
	void store_account(const data::account_data&, const boost::filesystem::path&);


}

#endif	