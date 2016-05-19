#include <iostream>
#include <fstream>
#include <QString>
#include <string>
#include <vector>
#include <set>
#include <codecvt>
#include <locale>
#include <QtGlobal>

#include "account.hpp"
#include "utility/stream_operations.hpp"
#include "utility/filesystem.hpp"
#include "utility/file_loader.hpp"

namespace
{
	using utf_convert = std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>;

	data::account_data load_basic_account(const boost::filesystem::path&);



	/**
	Loads basic information about an account.
	*/
	inline data::account_data load_basic_account(const boost::filesystem::path& p)
	{
		using utility::in_mem;
		using utility::read_string;

		data::account_data account;
		std::ifstream in{p.string(), std::ios::binary};
		std::string temps;

		if (in.good())
		{
			in_mem(in, account.id);
			read_string(in, temps);

			account.name = QString::fromStdString(temps);
			for (std::string::iterator it{ temps.begin() }; it != temps.end(); ++it) (*it) = 0;
		}
		in.close();
		return account;
	}


}

//stream operators:
namespace data
{
    std::ostream& operator<<(std::ostream& out, const transaction_data& t)
    {
        using utility::out_mem;
        using utility::write_string;
        
        if(out.good())
        {
            out_mem(out, t.value);
            out_mem(out, t.date);
            write_string(out, t.name.toStdString());
            write_string(out, t.description.toStdString());
        }
        return out;
    }
    
    std::istream& operator>>(std::istream& in, transaction_data& t)
    {
        using utility::in_mem;
        using utility::read_string;
        
        t = transaction_data{(decltype(t.value))0, (qint64)0, "", ""};
        std::string temps;
        
        in.peek();
        if(in.good())
        {
            in_mem(in, t.value);
			in_mem(in, t.date);
            
            read_string(in, temps);
            t.name = QString::fromStdString(temps);
            for(std::string::iterator it{temps.begin()}; it != temps.end(); ++it) (*it) = 0; 
            
            read_string(in, temps);
            t.description = QString::fromStdString(temps);
            for(std::string::iterator it{temps.begin()}; it != temps.end(); ++it) (*it) = 0;
        }
        return in;
    }
    
    std::ostream& operator<<(std::ostream& out, const account_data& account)
    {
        using utility::out_mem;
        using utility::write_string;
        using utility::write_vector;
        
        if(out.good())
        {
            out_mem(out, account.id);
            write_string(out, account.name.toStdString());
            write_vector<transaction_data>(out, account.transactions);
        }
        return out;
    }
    
    std::istream& operator>>(std::istream& in, account_data& account)
    {
        using utility::in_mem;
        using utility::read_string;
        using utility::read_vector;
        
        std::string temps;
        
        in.peek();
        if(in.good())
        {
            in_mem(in, account.id);
            read_string(in, temps);
            
            account.name = QString::fromStdString(temps);
            for(std::string::iterator it{temps.begin()}; it != temps.end(); ++it) (*it) = 0;
            
            read_vector<transaction_data>(in, account.transactions);
        }
        return in;
    }
    
    
}

//account_data member functions:
namespace data
{
	::utility::ID_T account_data::load_id(std::istream& in)
	{
		using utility::in_mem;

		utility::ID_T id{0};
		if(in.good()) in_mem(in, id);
		return id;
	}

	account_data account_data::basic(std::istream& in)
	{
		using utility::in_mem;
		using utility::read_string;

		account_data account;

		in.peek();
		if(in.good())
		{
			in_mem(in, account.id);

			{
				std::string temps;
				read_string(in, temps);
				account.name = QString::fromStdString(temps);
				for(auto it = temps.begin(); it != temps.end(); ++it) *it = 0;
			}
		}
		return account;
	}

	boost::filesystem::path account_data::FOLDER{(global::root / boost::filesystem::path{"Accounts"})};


}

//misc functions:
namespace data
{
	/**
	 Calculates the resulting balance each transaction results in after application to the account.
	 The index of each result corresponds to its index in the list of transactions passed as the argument.
	*/
	std::vector<int_least32_t> calculate_resulting_balances(const std::vector<transaction_data>& transactions)
	{
		std::vector<int_least32_t> results;
		
		for(std::size_t x{(transactions.size() - 1)}; true; --x)
		{
			if(!results.empty())
			{
				results.insert(results.begin(), (results.front() + transactions[x].value));
			}
			else results.insert(results.begin(), transactions[x].value);

			if(x == 0) break;
		}
		return results;
	}


}

