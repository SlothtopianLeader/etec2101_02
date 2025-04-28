#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <string>
#include "ordered_set.h"

#define EXECUTE_ORDERED_SET_TESTS 1
#if EXECUTE_ORDERED_SET_TESTS

/*
class OrderedSetTestFixture : public ::testing::Test
{
protected:
	void SetUp() override
	{
		fset.insert(1.1f);
		fset.insert(2.2f);
		fset.insert(1.1f);
		fset.insert(3.3f);
		fset.insert(0.5f);
	}

	void TearDown() override
	{

	}
	ssuds::OrderedSet<float> fset;
};

TEST_F(OrderedSetTestFixture, ContainsItems)
{
	ssuds::OrderedSet<float> fset;
	EXPECT_TRUE(fset.insert(10.2));
	EXPECT_TRUE(fset.contains(10.2));

	EXPECT_TRUE(fset.insert(5.3));
	EXPECT_FALSE(fset.insert(5.3));
	EXPECT_TRUE(fset.insert(2.7));
	EXPECT_TRUE(fset.contains(5.3));

	EXPECT_TRUE(fset.contains(2.7));
	EXPECT_FALSE(fset.contains(20.1));
}

TEST_F(OrderedSetTestFixture, ClearAndSize)
{
	ssuds::OrderedSet<float> fset;
	fset.insert(5.3);
	fset.insert(2.7);
	fset.insert(10.2);
	fset.insert(4.5);
	EXPECT_TRUE(fset.contains(2.7));
	fset.clear();
	EXPECT_FALSE(fset.contains(2.7));
	EXPECT_EQ(fset.get_height(), 0);
}

TEST_F(OrderedSetTestFixture, GetHeight)
{
	ssuds::OrderedSet<float> fset;
	EXPECT_EQ(fset.get_height(), 0);

	fset.insert(5.3);
	fset.insert(2.7);
	EXPECT_EQ(fset.get_height(), 2);

	fset.insert(10.2);
	fset.insert(4.5);
	EXPECT_EQ(fset.get_height(), 3);
}

TEST_F(OrderedSetTestFixture, Traversals)	// Test not complete
{
	ssuds::OrderedSet<float> fset;
	fset.insert(5.3);
	fset.insert(2.7);
	fset.insert(10.2);
	fset.insert(4.5);
	fset.insert(7.8);

	auto inOrder = fset.traversal(ssuds::TraversalType::INORDER);

	auto preOrder = fset.traversal(ssuds::TraversalType::PREORDER);

	auto postOrder = fset.traversal(ssuds::TraversalType::POSTORDER);
}


TEST_F(OrderedSetTestFixture, Rebalance)	// Test not complete
{
	ssuds::OrderedSet<float> fset;
	fset.insert(1.1);
	fset.insert(2.2);
	fset.insert(3.4);
	fset.insert(4.5);
	fset.insert(5.3);
	EXPECT_EQ(fset.get_height(), 5);
	fset.rebalance();
	EXPECT_LE(fset.get_height(), 3);

	auto inOrder = fset.traversal(ssuds::TraversalType::INORDER);
}

TEST_F(OrderedSetTestFixture, Erase)
{
	ssuds::OrderedSet<float> fset;
	fset.insert(5.3);
	fset.insert(2.7);
	fset.insert(10.2);
	fset.insert(4.5);
	fset.insert(7.8);
	fset.insert(3.2);
	fset.insert(8.1);

	EXPECT_TRUE(fset.erase(3.2));
	EXPECT_FALSE(fset.contains(3.2));

	EXPECT_TRUE(fset.erase(4.5));
	EXPECT_FALSE(fset.contains(4.5));

	EXPECT_TRUE(fset.erase(5.3));
	EXPECT_FALSE(fset.contains(5.3));
}

TEST_F(OrderedSetTestFixture, GetParent)
{
	ssuds::OrderedSet<float> fset;
	fset.insert(5.3);
	fset.insert(2.7);
	fset.insert(10.2);
	fset.insert(4.5);
	fset.insert(7.8);
	fset.insert(3.2);
	fset.insert(8.1);

	auto p1 = fset.get_parent(4.5);
	// std::cout << "P1 value: " << p1.has_value() << "\n";		// 1
	ASSERT_TRUE(p1.has_value());
	EXPECT_EQ(p1.value(), 2.7f);
	
	auto p2 = fset.get_parent(10.2);
	ASSERT_TRUE(p2.has_value());
	EXPECT_EQ(p2.value(), 5.3f);

	auto p3 = fset.get_parent(8.1);
	ASSERT_TRUE(p3.has_value());
	EXPECT_EQ(p3.value(), 7.8f);
}

TEST_F(OrderedSetTestFixture, Iterator)
{
	ssuds::OrderedSet<float> fset;
	fset.insert(5.3);
	fset.insert(2.7);
	fset.insert(10.2);
	fset.insert(4.5);
	fset.insert(7.8);
	fset.insert(3.2);
	fset.insert(8.1);

	std::stringstream ss;
	for (auto it = fset.begin(); it != fset.end(); ++it)
	{
		ss << *it << " ";
	}
	std::cout << "Current Values: " << ss.str() << "\n";
	EXPECT_EQ(ss.str(), "2.7 3.2 4.5 5.3 7.8 8.1 10.2 ");
}
*/
#endif