#include <gtest/gtest.h>
#include <vector>
#include <unit_tests_array_list.h>
#include <string>
#include "array_list_utility.h"
#include "linked_list.h"


int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


/*
int main() {
	ssuds::LinkedList<std::string> list;
	list.prepend("C");
	list.append("D");
	list.insert("B", 0);
	list.insert("A", 0);

	list.output(std::cout); // Should print: A -> B -> C -> D
	std::cout << "0: " << list[0] << std::endl;
	std::cout << "1: " << list[1] << std::endl;
	std::cout << "2: " << list[2] << std::endl;
	std::cout << "3: " << list[3] << std::endl;

	return 0;
}
*/