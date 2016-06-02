#ifdef UNIT_TEST_PROG
#include <cstdlib>
#include <limits>
#include <QDate>
#include <vector>

#include "random_data.hpp"
#include "data/account.hpp"
#include "utility/file_loader.hpp"

namespace common
{
	unsigned int random_number(const unsigned int& min, const unsigned int& max)
	{
		return ((rand() % ((max + 1) - min)) + min);
	}

	unsigned int random_number()
	{
		return random_number(0, std::numeric_limits<unsigned int>::max());
	}

	signed int signed_random_number(const int& min, const int& max)
	{
		return (signed int)((rand() % ((max + 1) - min)) + min);
	}

	signed int signed_random_number()
	{
		return (signed int)signed_random_number(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
	}

	unsigned char random_character(const std::string& chars)
	{
		return chars[random_number(0, (unsigned int)(chars.size() - 1))];
	}

	std::string random_string(const unsigned int& min, const unsigned int& max, const std::string& chars)
	{
		std::string temps;
		std::size_t size{random_number(min, max)};

		for(std::size_t x{0}; x < size; ++x) temps += random_character(chars);
		return temps;
	}

	std::string random_string(const std::string& s)
	{
		return random_string(5, 100, s);
	}

	data::transaction_data random_transaction()
	{
		return data::transaction_data{signed_random_number(-10000, 10000),
									  (qint64)random_number((QDate::currentDate().toJulianDay() - 365), (QDate::currentDate().toJulianDay() + 365)),
									  QString::fromStdString(random_string(10, 100)),
									  QString::fromStdString(random_string(100, 500))};
	}

	data::account_data random_account()
	{
		data::account_data account{QString::fromStdString(random_string(10, 100)),
								   (utility::ID_T)random_number(0, 500),
								   std::vector<data::transaction_data>{}};
		std::size_t size{random_number(0, 5000)};
		for(std::size_t x{0}; x < size; ++x)
		{
			account.transactions.push_back(random_transaction());
		}
		return account;
	}


}


#endif
