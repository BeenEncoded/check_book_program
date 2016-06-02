#ifdef UNIT_TEST_PROG
#ifndef UNIT_TESTING_RANDOM_DATA_HPP_INCLUDED
#define UNIT_TESTING_RANDOM_DATA_HPP_INCLUDED
#include <string>

#include "data/global.hpp"
#include "data/account.hpp"

namespace common
{
	unsigned int random_number(const unsigned int&, const unsigned int&);
	unsigned int random_number();
	signed int signed_random_number(const int&, const int&);
	signed int signed_random_number();
	unsigned char random_character(const std::string& = std::string{global::chars});
	std::string random_string(const unsigned int&, const unsigned int&, const std::string& = std::string{global::chars});
	std::string random_string(const std::string& = std::string{global::chars});
	data::transaction_data random_transaction();
	data::account_data random_account();

}

#endif
#endif