// Lab02.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "array_list.h"

int main(int argc, char** argv)
{
    ssuds::ArrayList<int> ilist;
    ilist.append(15);
    ilist.append(16);
    ilist.prepend(14);
    ilist.prepend(13);

    ssuds::ArrayList<std::string> slist;
}