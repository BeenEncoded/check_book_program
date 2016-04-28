#include <iostream>
#include <fstream>
#include <QString>
#include <string>
#include <vector>
#include <set>
#include <codecvt>
#include <locale>

#include "account.hpp"
#include "utility/stream_operations.hpp"
#include "utility/filesystem.hpp"

namespace
{
	using utf_convert = std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>;

	data::account_data load_account(const boost::filesystem::path&);
	data::account_data load_basic_account(const boost::filesystem::path&);
	decltype(data::account_data::id) load_id(const boost::filesystem::path&);



	inline data::account_data load_account(const boost::filesystem::path& p)
	{
		using boost::filesystem::is_regular_file;

		data::account_data account{"", data::account_data::NOID, std::vector<data::transaction_data>{}};

		if(is_regular_file(p))
		{
			std::ifstream in{p.string().c_str(), std::ios::binary};
			if(in.good()) in>> account;
			in.close();
		}
		return account;
	}

	inline data::account_data load_basic_account(const boost::filesystem::path& p)
	{
		using utility::in_mem;
		using utility::read_string;

		data::account_data account;
		std::ifstream in{p.string(), std::ios::binary};

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

	inline decltype(data::account_data::id) load_id(const boost::filesystem::path& p)
	{
		using boost::filesystem::is_regular_file;
		using utility::in_mem;

		decltype(data::account_data::id) id{0};

		if(is_regular_file(p))
		{
			std::ifstream in{p.string(), std::ios::binary};
			if(in.good()) in_mem(in, id);
			in.close();
		}
		return id;
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
            out<< t.date;
            write_string(out, t.name.toStdString());
            write_string(out, t.description.toStdString());
        }
        return out;
    }
    
    std::istream& operator>>(std::istream& in, transaction_data& t)
    {
        using utility::in_mem;
        using utility::read_string;
        
        t = transaction_data{(decltype(t.value))0, tdata::time_class{}, "", ""};
        std::string temps;
        
        in.peek();
        if(in.good())
        {
            in_mem(in, t.value);
            in>> t.date;
            
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

namespace data
{
	namespace file
	{
		/**
		 * Loads a list of the available accounts.  Only loads basic information
		 * for each account in order to conserve memory.  Meant for things like menus.
		*/
		std::vector<account_data> load_basic(const boost::filesystem::path& folder)
		{
			using boost::filesystem::is_directory;
			using boost::filesystem::is_regular_file;
			using boost::filesystem::is_symlink;
			using filesystem::glob;

			std::vector<account_data> accounts;
			
			if(is_directory(folder) && !is_symlink(folder))
			{
				for(glob it{folder, account_data::REGEX}; !it.end(); ++it)
				{
					if(is_regular_file(*it))
					{
						accounts.push_back(load_basic_account(it->path()));
						if(accounts.back().id == account_data::NOID) accounts.pop_back();
					}
				}
			}
			return accounts;
		}

		std::vector<account_data> load(const boost::filesystem::path& folder)
		{
			using boost::filesystem::is_directory;
			using boost::filesystem::is_symlink;
			using boost::filesystem::is_regular_file;
			using ::filesystem::glob;

			std::vector<account_data> accounts;

			if(is_directory(folder) && !is_symlink(folder))
			{
				for(glob it{folder, account_data::REGEX}; !it.end(); ++it)
				{
					if(is_regular_file(it->path()))
					{
						accounts.push_back(load_account(it->path()));
						if(accounts.back().id == 0) accounts.pop_back();
					}
				}
			}
			return accounts;
		}

		std::set<decltype(account_data::id)> account_ids(const boost::filesystem::path& folder)
		{
			using filesystem::glob;
			using boost::filesystem::is_directory;
			using boost::filesystem::is_symlink;
			using boost::filesystem::is_regular_file;

			std::set<decltype(account_data::id)> i;

			if(is_directory(folder) && !is_symlink(folder))
			{
				for(glob it{folder, account_data::REGEX}; !it.end(); ++it)
				{
					if(is_regular_file(*it))
					{
						i.insert(load_id(it->path()));
					}
				}
				if(i.find(account_data::NOID) != i.end()) i.erase(i.find(account_data::NOID)); //remove invalid ids
			}
			return i;
		}

		void save(const account_data& account, const boost::filesystem::path& folder)
		{
			using boost::filesystem::is_directory;
			using boost::filesystem::is_symlink;
			using boost::filesystem::create_directories;
			using filesystem::glob;
			using boost::filesystem::path;
			using boost::filesystem::exists;

			if(!is_directory(folder) && !is_symlink(folder)) create_directories(folder);

			//assign a new id if it isn't already assigned a valid one:
			if(account.id == account_data::NOID)
			{
				auto i = account_ids();
				while(i.find(++account.id) != i.end());
			}

			path file;

			//find its file
			for(glob it{folder, account_data::REGEX}; (!it.end() && !exists(file)); ++it)
			{
				if(is_regular_file(*it))
				{
					if(load_id(it->path()) == account.id)
					{
						file = it->path();
					}
				}
			}

			//if we didn't find its file, create a filename for it:
			if(!exists(file))
			{
				file = (folder / path{std::to_string(account.id) + utf_convert{}.to_bytes(account_data::FILE_EXTENSION)});
			}

			std::ofstream out{file.string(), std::ios::binary};
			out<< account;
			out.close();
		}

		void remove(const account_data& account, const boost::filesystem::path& folder)
		{
			using filesystem::glob;
			using boost::filesystem::is_directory;
			using boost::filesystem::is_symlink;
			using boost::filesystem::is_regular_file;

			if(is_directory(folder) && !is_symlink(folder))
			{
				for(glob it{folder, account_data::REGEX}; !it.end(); ++it)
				{
					if(is_regular_file(*it))
					{
						if(load_id(it->path()) == account.id)
						{
							boost::filesystem::remove(it->path());
							return;
						}
					}
				}
			}
		}


	}
}

