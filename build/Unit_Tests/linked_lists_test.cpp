#include <gtest/gtest.h>
#include "linked_list.h"

#define EXECUTE_LINKED_LIST_TESTS 1
#if EXECUTE_LINKED_LIST_TESTS

// Do you understand the difference betweeen a Fixture (a class derived from ::testing::Test),
// and a test-function?  They're almost identical -- the advantage of a fixture is you can put
// common code in there (like making an ArrayList with a few items in it) without having to put
// that code explicitly in each test case.
class LinkedListTestFixture : public ::testing::Test
{
protected:
	void SetUp() override
	{
		slist2.append("B");
		slist2.append("C");
		slist2.prepend("A");
		//slist2.insert("D", 3);
	}

	void TearDown() override
	{
	}
	ssuds::LinkedList<std::string> slist1;
	ssuds::LinkedList<std::string> slist2;
};

TEST_F(LinkedListTestFixture, InitiallyEmpty)
{
	EXPECT_EQ(slist1.size(), 0);
}


TEST_F(LinkedListTestFixture, AddingItems)
{
	ASSERT_EQ(slist2.size(), 4);
	EXPECT_EQ(slist2[0], "A");
	EXPECT_EQ(slist2[1], "B");
	EXPECT_EQ(slist2[2], "C");
	//EXPECT_EQ(slist2[3], "D");
}
#endif