#ifdef UNIT_TEST_PROG
#ifndef UNIT_TESTING_TEST_HPP_INCLUDED
#define UNIT_TESTING_TEST_HPP_INCLUDED
#include <UnitTest++/UnitTest++.h>
#include <QCoreApplication>
#include <cstdlib>
#include <ctime>

#include "unit_testing/database_tests/tests.hpp"

namespace
{
	inline void test()
	{
		srand(std::time(nullptr));
		QCoreApplication::exit(UnitTest::RunAllTests());
	}
}

#endif
#endif