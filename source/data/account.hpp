#ifndef DATA_ACCOUNT_HPP_INCLUDED
#define DATA_ACCOUNT_HPP_INCLUDED
#include <QString>
#include <vector>
#include <iostream>
#include <boost/filesystem.hpp>
#include <set>
#include <QDate>
#include <QtGlobal>

#include "utility/time_class.hpp"
#include "utility/file_loader.hpp"
#include "data/global.hpp"

namespace data
{
	using value_t = int_least64_t;

    struct account_data;
    struct transaction_data;
    
	std::vector<value_t> calculate_resulting_balances(const std::vector<transaction_data>&);

    std::ostream& operator<<(std::ostream&, const account_data&);
    std::istream& operator>>(std::istream&, account_data&);
    
    std::ostream& operator<<(std::ostream&, const transaction_data&);
    std::istream& operator>>(std::istream&, transaction_data&);
    
    struct transaction_data
    {
        value_t value; //the monetary value of this transaction multiplied by 100.
        qint64 date;
        QString name, description;
    };
    
    struct account_data
    {
        QString name;
        utility::ID_T id;
        std::vector<transaction_data> transactions; //A list of transactions beginning with the most recent (index 0) and ending with the oldest

		static boost::filesystem::path& folder()
		{
			static boost::filesystem::path f{(global::root / boost::filesystem::path{ "Accounts" })};
			return f;
		}

		static constexpr const char* const EXTENSION{".account"};

		static utility::ID_T load_id(std::istream&);
		static account_data basic(std::istream&);
    };

}

#endif