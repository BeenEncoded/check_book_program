#ifndef DATA_ACCOUNT_HPP_INCLUDED
#define DATA_ACCOUNT_HPP_INCLUDED
#include <QString>
#include <vector>
#include <iostream>
#include <boost/filesystem.hpp>
#include <set>

#include "utility/time_class.hpp"
#include "data/global.hpp"

namespace data
{
    struct account_data;
    struct transaction_data;
    
    
    std::ostream& operator<<(std::ostream&, const account_data&);
    std::istream& operator>>(std::istream&, account_data&);
    
    std::ostream& operator<<(std::ostream&, const transaction_data&);
    std::istream& operator>>(std::istream&, transaction_data&);
    
    struct transaction_data
    {
        int_least32_t value;
        tdata::time_class date;
        QString name, description;
    };
    
    struct account_data
    {
        QString name;
        int_least16_t id; //supports 65,536 account ids... I think that will be fine.
        std::vector<transaction_data> transactions;

		static constexpr const wchar_t* const FILE_EXTENSION{L".account"};
		static constexpr const wchar_t* const FOLDER_NAME{L"Accounts"};
		static constexpr int_least16_t NOID{0};

		static constexpr const char* const REGEX{"**.account$"};
    };
    
	namespace file
	{
		using boost::filesystem::path;

		std::vector<account_data> load_basic(const path& = (global::root / path{account_data::FOLDER_NAME}));
		account_data load_account(const decltype(account_data::id)&, const path& = (global::root / path{account_data::FOLDER_NAME}));
		std::vector<account_data> load(const path& = (global::root / path{account_data::FOLDER_NAME}));
		std::set<decltype(account_data::id)> account_ids(const path& = (global::root / path{account_data::FOLDER_NAME}));
		void save(account_data&, const path& = (global::root / path{account_data::FOLDER_NAME}));
		void remove(const decltype(account_data::id)&, const path& = (global::root / path{account_data::FOLDER_NAME}));

	}


}

#endif