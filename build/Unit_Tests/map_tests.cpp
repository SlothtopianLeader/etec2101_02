#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <string>
#include "map.h"

class MapTestFixture : public ::testing::Test
{
protected:
	void SetUp() override
	{
		fset["audri"] = 19.9f;
		fset["ryanne"] = 19.1f;
		fset["colton"] = 21.9f;
		fset["hank"] = 28.4f;
		fset["derrick"] = 30.3f;
	}

	void TearDown() override
	{

	}
	ssuds::Map<std::string, float> fset;
};

TEST_F(MapTestFixture, Contains)
{
	EXPECT_TRUE(fset.contains("audri"));
	EXPECT_TRUE(fset.contains("ryanne"));
	EXPECT_TRUE(fset.contains("colton"));
	EXPECT_TRUE(fset.contains("hank"));
	EXPECT_TRUE(fset.contains("derrick"));
	EXPECT_FALSE(fset.contains("chase"));
}

TEST_F(MapTestFixture, Find)
{
	EXPECT_FLOAT_EQ(fset["audri"], 19.9f);
	EXPECT_FLOAT_EQ(fset["ryanne"], 19.1f);
	EXPECT_FLOAT_EQ(fset["colton"], 21.9f);
	EXPECT_FLOAT_EQ(fset["hank"], 28.4f);
	EXPECT_FLOAT_EQ(fset["derrick"], 30.3f);
}

TEST_F(MapTestFixture, Remove)
{
	EXPECT_TRUE(fset.remove("hank"));
	EXPECT_FALSE(fset.contains("hank"));
	EXPECT_EQ(fset.capacity(), 8);

	EXPECT_FALSE(fset.remove("chase"));
}

TEST_F(MapTestFixture, Insert)
{
	fset["hank"] = 29.0;
	EXPECT_FLOAT_EQ(fset["hank"], 29.0);
}