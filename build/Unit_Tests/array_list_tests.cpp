#include <gtest/gtest.h>
#include <vector>
#include "cleaned_up_arraylist.h"
#include "person.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>


class ArrayListTestFixture : public ::testing::Test {
protected:
    ssuds::ArrayList<float> slist;

    void SetUp() override {
    }

    void TearDown() override {
        slist.clear();
    }
};

TEST_F(ArrayListTestFixture, AddingItems)
{
    ssuds::ArrayList<float> slist;
    slist.append(2.3f);
    slist.append(2.6f);

    ASSERT_EQ(slist.size(), 4);
    EXPECT_EQ(slist[0], "A");
    EXPECT_EQ(slist[0], "B");
    EXPECT_EQ(slist[0], "C");
    EXPECT_EQ(slist[0], "D");
}

TEST_F(ArrayListTestFixture, InsertingItems)
{
    ssuds::ArrayList<float> slist;
    slist.insert(1.8f, 0);
    slist.insert(2.2f, 1);
    slist.insert(4.2f, 3);
    EXPECT_FLOAT_EQ(slist.at(0), 1.8f);
    EXPECT_FLOAT_EQ(slist.at(1), 2.2f);
    EXPECT_FLOAT_EQ(slist.at(3), 4.2f);
}

TEST_F(ArrayListTestFixture, GrowItems)
{
    ssuds::ArrayList<float> slist;

    EXPECT_EQ(slist.size(), 5);
    EXPECT_EQ(slist.capacity(), 5);

    slist.append(5.6f);
    slist.append(2.2f);
    EXPECT_EQ(slist.size(), 7);
    EXPECT_GE(slist.capacity(), 10);
    EXPECT_FLOAT_EQ(slist.at(5), 5.6f);
    EXPECT_FLOAT_EQ(slist.at(6), 2.2f);
}

TEST_F(ArrayListTestFixture, Stream)
{
    ssuds::ArrayList<float> slist;
    EXPECT_EQ(slist.size(), 7);                                     //     [1.8, 2.2, 2.2, 3.6, 4.2, 5.6, 2.2]
}

TEST(ArrayListTestFixture, StreamOperator)
{
    ssuds::ArrayList<std::string> slist;
    std::stringstream ss;

    ss << slist;
    EXPECT_EQ(ss.str(), "[]");

    ss.str("");
    slist.append("A");

    ss << slist;        // [A]
    EXPECT_EQ(ss.str(), "[A]");

    ss.str("");
    slist.append("B");
    slist.append("C");
    slist.append("D");
    ss << slist;
    EXPECT_EQ(ss.str(), "[A, B, C, D]");
    ss.str("");
    slist.output(ss);
    EXPECT_EQ(ss.str(), "[A, B, C, D]");
}

TEST_F(ArrayListTestFixture, FindAllItems)
{
    ssuds::ArrayList<float> slist;
    int index = slist.find(2.2f, 0);

    // EXPECT_FLOAT_EQ(slist.find(2.2f, index));
    while (index != -1)
    {
        std::cout << "\tFound occurrence of 2.2 at index " << index << "\n";
        index++;
        if (index == slist.size())
            break;
        index = slist.find(2.2f, index);
    }
}

TEST_F(ArrayListTestFixture, RemoveItems)
{
    ssuds::ArrayList<float> slist;
    EXPECT_EQ(slist.size(), 7);
    EXPECT_GE(slist.capacity(), 10);
    slist.remove_all(2.2f);
    EXPECT_EQ(slist.size(), 4);
    EXPECT_GE(slist.capacity(), 5);
}

TEST_F(ArrayListTestFixture, CopyItems)
{
    ssuds::ArrayList<float> slist;
    ssuds::ArrayList<float> slist2(slist);
    ssuds::ArrayList<float> slist3 = slist;
    slist.append(7.7f);
    slist2[1] = 999.99f;
    slist3.clear();
    EXPECT_FLOAT_EQ(slist.at(6), 7.7f);
    EXPECT_FLOAT_EQ(slist2.at(1), 999.99f);
}

TEST_F(ArrayListTestFixture, Operator1)         // = Operator
{
    ssuds::ArrayList<float> slist;
    ssuds::ArrayList<float> slist2;
    ssuds::ArrayList<float> slist3;
    ssuds::ArrayList<float> slist4;

    slist4 = slist2 = slist;
    slist.clear();
    slist3.append(8.8f);
    slist3.append(9.9f);
    EXPECT_EQ(slist.size(), 0);
    EXPECT_EQ(slist3.size(), 2);
}

TEST_F(ArrayListTestFixture, Operator2)         // [] Operator
{
    ssuds::ArrayList<float> slist;
    slist[0] = 1.11f;
    EXPECT_FLOAT_EQ(slist.at(0), 1.11f);
}

TEST_F(ArrayListTestFixture, BasicIterator)
{
    ssuds::ArrayList<float> slist2;

    slist2.append(1.11f);
    slist2.append(2.2f);
    slist2.append(3.3f);
    slist2.append(4.4f);
    slist2.append(5.5f);
    slist2.append(6.6f);
    slist2.append(7.7f);

    EXPECT_EQ(slist2.size(), 7);
    float expectedValues[] = { 1.11f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f };
    int index = 0;
    for (float f : slist2)
    {
        EXPECT_FLOAT_EQ(f, expectedValues[index]) << "Index does not match." << index;
        index++;
    }

    ssuds::ArrayList<float>::ArrayListIterator it = slist2.begin();
    index = 0;
    while (it != slist2.end())
    {
        EXPECT_FLOAT_EQ(*it, expectedValues[index]) << "Index does not match." << index;
        ++it;
        index++;
    }

    EXPECT_EQ(index, 7);
}

TEST_F(ArrayListTestFixture, OtherIterator)         // Finish Me Bruh
{
    ssuds::ArrayList<float> slist2;

    slist2.append(1.11f);
    slist2.append(2.2f);
    slist2.append(3.3f);
    slist2.append(4.4f);
    slist2.append(5.5f);
    slist2.append(6.6f);
    slist2.append(7.7f);

    EXPECT_EQ(slist2.size(), 7);
    float expectedValues[] = { 1.11f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f };
    int index = 0;
    for (float f : slist2)
    {
        EXPECT_FLOAT_EQ(f, expectedValues[index]) << "Index does not match." << index;
        index++;
    }

    ssuds::ArrayList<float>::ArrayListIterator it = slist2.begin();
    index = 0;
    while (it != slist2.end())
    {
        EXPECT_FLOAT_EQ(*it, expectedValues[index]) << "Index does not match." << index;
        ++it;
        index++;
    }

    EXPECT_EQ(index, 7);
}

TEST_F(ArrayListTestFixture, ReverseIterator)
{
    ssuds::ArrayList<float> slist2;

    slist2.append(1.11f);
    slist2.append(2.2f);
    slist2.append(3.3f);
    slist2.append(4.4f);
    slist2.append(5.5f);
    slist2.append(6.6f);
    slist2.append(7.7f);

    ssuds::ArrayList<float>::ArrayListIterator it = slist.rbegin();
    int index = 0;
    while (it != slist2.rend())								//      7.7 6.6 5.5 4.4 3.3 2.2 1.11
    {
        EXPECT_FLOAT_EQ(*it, index);
        ++it;
        index++;
    }

    // This is one way to test the move-constructor
    ssuds::ArrayList<float> slist5(std::move(slist2));
    EXPECT_EQ(slist2.size(), 0);
    EXPECT_EQ(slist2.capacity(), 0);
}
/*
TEST_F(ArrayListTestFixture, ReserveItems)
{
    std::cout << "\ntest 7 (reserve and Person's):\n=====\n";       // test7 (reserve and Person's)
    ssuds::ArrayList<example::Person> plist;                        // =====
    std::cout << "\tplist size=" << plist.size() << "\n";           //     plist size=0
    std::cout << "\tplist capacity=" << plist.capacity() << "\n";   //     plist capacity=5
    char temp_string[4] = { 0, 0, 0, 0 };
    plist.reserve(26);
    std::cout << "\tplist size=" << plist.size() << "\n";           //     plist size=0
    std::cout << "\tplist capacity=" << plist.capacity() << "\n";   //     plist capacity=26
    for (unsigned int i = 0; i < 26; i++)
    {
        temp_string[0] = 'A' + i;
        temp_string[1] = temp_string[2] = 'a' + i;
        example::Person p(std::string(temp_string), "Smith", 100 + i, i + 0.5f);
        plist.append(p);
        plist.at(plist.size() - 1).set_hours_worked(i * 2);
    }
    plist.insert(example::Person("---", "###", 5000, 0.0f), 1);
    std::cout << "\tplist size=" << plist.size() << "\n";           //     plist size=26
    std::cout << "\tplist capacity=" << plist.capacity() << "\n";   //     plist capacity=26
    std::cout << std::setprecision(2) << std::fixed;
    for (unsigned int i = 0; i < plist.size(); i++)                 //     Aaa Smith $0.00
    {                                                               //     --- ### $0.00
        example::Person p = plist.at(i);                            //     Bbb Smith $3.00
        std::cout << "\t" << p.get_name(false) << " ";              //     Ccc Smith $10.00
        std::cout << " $" << p.get_salary() << "\n";                //     Ddd Smith $21.00
    }                                                               //     Eee Smith $36.00
                                                                    //     (more)
                                                                    //     Zzz Smith $1275.00

#
    return 0;
}
*/