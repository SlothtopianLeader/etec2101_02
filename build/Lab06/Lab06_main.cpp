#include "linked_lists.h"
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
	ssuds::LinkedList<std::string> slist;
	slist.append("Bob");
	slist.append("Carl");
	slist.append("Doug");
	slist.append("Erin");
	slist.append("Henry");
	slist.insert("Frank", 4);

	slist.output(std::cout);		// [Bob, Carl, Doug, Erin, Frank, Henry]

	std::cout << "iterator\n========\n";
	ssuds::LinkedList<std::string>::LinkedListIterator it = slist.begin();
	while (it != slist.end())
	{
		std::string temp = *it;
		std::cout << "\t" << temp;
		++it;
	}

	std::cout << "for-each\n========\n";
	for (std::string s : slist)
		std::cout << "\t" << s << "\n";
}