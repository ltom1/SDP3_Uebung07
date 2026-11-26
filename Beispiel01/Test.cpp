#include "gtest/gtest.h"

#include <vld.h>
#include <sstream>

#include "CarRental.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////

TEST(CarRental, nullptr) {
	CarRental rental;
	
	try {
		rental.Add(nullptr);
		FAIL();
	}
	catch (std::invalid_argument const& ex) {
		EXPECT_STREQ(ex.what(), "Provided car was nullptr");
	}

	try {
		rental.Back(nullptr);
		FAIL();
	}
	catch (std::runtime_error const& ex) {
		EXPECT_STREQ(ex.what(), "Provided car was not found");
	}

	try {
		rental.Reserve(nullptr);
		FAIL();
	}
	catch (std::runtime_error const& ex) {
		EXPECT_STREQ(ex.what(), "Provided car was not found");
	}
}

TEST(CarRental, Empty) {
	ostringstream ost;
	CarRental rental;
	
	rental.PrintAvailable(ost);
	EXPECT_EQ(ost.str(), "");
	ost.str("");

	rental.PrintReserved(ost);
	EXPECT_EQ(ost.str(), "");
	ost.str("");

	EXPECT_TRUE(rental.GetAvailable("", "").empty());
	EXPECT_TRUE(rental.GetReserved("", "").empty());
}

/////////////////////////////////////////////////////////////////////////////