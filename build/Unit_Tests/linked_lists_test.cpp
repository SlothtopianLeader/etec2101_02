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
		slist2.insert("D", 3);
	}

	void TearDown() override
	{

	}
	ssuds::LinkedList<std::string> slist1;
	ssuds::LinkedList<std::string> slist2;
	ssuds::LinkedList<int> ilist;
};

TEST_F(LinkedListTestFixture, InitiallyEmpty)
{
	EXPECT_EQ(slist1.size(), 0);
	EXPECT_EQ(ilist.size(), 0);
}


TEST_F(LinkedListTestFixture, AddingItems)
{
	ASSERT_EQ(slist2.size(), 4);
	EXPECT_EQ(slist2[0], "A");
	EXPECT_EQ(slist2[1], "B");
	EXPECT_EQ(slist2[2], "C");
	EXPECT_EQ(slist2[3], "D");
}

TEST_F(LinkedListTestFixture, MoreInsert)
{
	slist2.insert("pre_A", 0);			// [pre_A, A, B, C, D]
	slist2.insert("A2", 2);				// [pre_A, A, A2, B, C, D]
	slist2.insert("post_D", 6);			// [pre_A, A, A2, B, C, D, post_D]

	EXPECT_EQ(slist2.size(), 7);
	EXPECT_EQ(slist2.at(0), "pre_A");
	EXPECT_EQ(slist2.at(1), "A");
	EXPECT_EQ(slist2.at(2), "A2");
	EXPECT_EQ(slist2.at(3), "B");
	EXPECT_EQ(slist2.at(4), "C");
	EXPECT_EQ(slist2.at(5), "D");
	EXPECT_EQ(slist2.at(6), "post_D");

}

TEST_F(LinkedListTestFixture, Finding)
{
	for (int i : {10, 7, 10, 10, 9, 10, 5, 10})
		ilist.append(i);

	int index = ilist.find(7);
	EXPECT_EQ(index, 1);
	index = ilist.find(10, 0);
	for (int expected_index : {0, 2, 3, 5, 7})
	{
		EXPECT_EQ(index, expected_index);
		index = ilist.find(10, index + 1);
	}

	EXPECT_EQ(index, -1);
}
#endif