// Lab02.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "array_list.h"

// Reference for endl: https://www.geeksforgeeks.org/endl-vs-n-in-cpp/
int main()
{
	ssuds::ArrayList<float> float_list;

	std::cout << "test1:\n=====\n";		// Append test
	float_list.append(2.7f);
	float_list.append(3.3f);
	std::cout << "\tsize=" << float_list.size() << std::endl;
	std::cout << "\titem0=" << float_list.at(0) << std::endl;
	std::cout << "\titem1=" << float_list.at(1) << std::endl;

	std::cout << "test2:\n=====\n";		// Insert test
	float_list.insert(0, 1.2f);
	float_list.insert(3, 4.5f);
	float_list.insert(1, 2.9f);
	for (int i = 0; i < float_list.size(); i++)
		std::cout << "\titem" << i << "=" << float_list.at(i) << "\n";

	std::cout << "test3:\n=====\n";		// Prepend test
	float_list.prepend(1.1f);
	float_list.prepend(1.0f);
	for (int i = 0; i < float_list.size(); i++)
		std::cout << "\titem" << i << "=" << float_list.at(i) << "\n";
	std::cout << "\n";

	std::cout << "test4:\n=====\n";		// Output test
	std::cout << "Output: ";
	float_list.output(std::cout);
	std::cout << "\n" << std::endl;

	std::cout << "test5:\n=====\n";		// Remove test
	float_list.remove(1);
	float_list.remove(3);
	for (int i = 0; i < float_list.size(); i++)
		std::cout << "\titem" << i << "=" << float_list.at(i) << "\n";

	std::cout << "test6:\n=====\n";		// Remove all test
	float_list.remove_all(3.3);
	float_list.remove_all(2.9);
	for (int i = 0; i < float_list.size(); i++)
		std::cout << "\titem" << i << "=" << float_list.at(i) << "\n";

	std::cout << "test7:\n=====\n";		// Find test
	int index1 = float_list.find(4.5f);
	std::cout << "Occurences: " << index1 << "\n" << std::endl;

	std::cout << "test8:\n=====\n";		// Reserve test
	ssuds::ArrayList<int> int_list;

	std::cout << "Starting capacity: " << int_list.capacity() << std::endl;

	int_list.reserve(10);
	std::cout << "Capacity: " << int_list.capacity() << std::endl;

	int_list.append(1);
	int_list.append(2);
	int_list.append(3);

	std::cout << "After reserving space: \n";
	for (int i = 0; i < float_list.size(); i++)
		std::cout << "\titem" << i << "=" << float_list.at(i) << "\n";
	std::cout << std::endl;

	int_list.reserve(5);

	return 0;
}