#ifdef UNIT_TEST_PROG
#ifndef UNIT_TESTING_DATABASE_TESTS_CREATION_TEST_HPP_INCLUDED
#define UNIT_TESTING_DATABASE_TESTS_CREATION_TEST_HPP_INCLUDED
#include <UnitTest++/UnitTest++.h>

#include "db_creation.hpp"

TEST(db_creation_test_case)
{
	testing::create_db();
}

#endif
#endif