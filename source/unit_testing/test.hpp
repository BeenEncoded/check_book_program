#ifdef UNIT_TEST_PROG
#ifndef UNIT_TESTING_TEST_HPP_INCLUDED
#define UNIT_TESTING_TEST_HPP_INCLUDED
#include <UnitTest++/UnitTest++.h>
#include <QCoreApplication>
#include <cstdlib>
#include <ctime>
#include <botan/init.h>
#include <iostream>

//#include "unit_testing/database_tests/tests.hpp"
#include "unit_testing/encryption_tests/tests.hpp"

namespace
{
	inline void test()
	{
		using std::cout;
		using std::endl;

		try
		{
			Botan::LibraryInitializer init;
			srand(std::time(nullptr));
			QCoreApplication::exit(UnitTest::RunAllTests());
		}
		catch(const std::exception& e)
		{
			cout<< endl<< "EXCEPTION: \""<< e.what()<< "\""<< endl;
		}
	}
}

#endif
#endif