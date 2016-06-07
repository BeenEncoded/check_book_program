#ifdef UNIT_TEST_PROG
#ifndef UNIT_TESTING_ENCRYPTION_TESTS_FILE_TEST_TEST_HPP_INCLUDED
#define  UNIT_TESTING_ENCRYPTION_TESTS_FILE_TEST_TEST_HPP_INCLUDED
#include <UnitTest++/UnitTest++.h>

#include "file_test.hpp"

TEST(encrypted_file_test)
{
	CHECK(testing::encrypt_file());
}

#endif
#endif