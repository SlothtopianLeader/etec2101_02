// Lab02.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "array_list.h"

int main()
{
	ssuds::ArrayList<float> float_list;

	std::cout << "test1:\n=====\n";
	float_list.append(2.1f);
	float_list.append(3.6f);
	std::cout << "\tsize=" << float_list.size() << std::endl;
	std::cout << "\titem0=" << float_list.at(0) << std::endl;
	std::cout << "\titem1=" << float_list.at(1) << std::endl;

	std::cout << "test2:\n=====\n";
	float_list.insert(0, 1.8f);
	float_list.insert(3, 4.3f);
	float_list.insert(1, 2.0f);
	for (int i = 0; i < float_list.size(); i++)
		std::cout << "\titem" << i << "=" << float_list.at(i) << "\n";

	return 0;
}