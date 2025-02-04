#include <iostream>
#include <string>
#include <fstream>		//access to FILE input/output
#include <iomanip>		// Needed for setting precision
#include "person_database.h"

int main(int argc, char** argv)
{
	example::PersonDatabase DB("..\\..\\media\\person_database.txt");

	while (true)
	{

		std::cout << "\nMenu: \n" << "1. Add Person\n" << "2. Remove Person\n" << "3. Print Database\n" << "4. Quit\n" << "Enter your option: ";

		int option;
		std::cin >> option;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "Invalid number.\n";
			continue;
		}
		
		if (option == 1)	// Add
		{
			int id;
			std::string fname, lname;
			float hourly_rate;
			unsigned int hours_worked;

			std::cout << "Enter ID: ";
			std::cin >> id;
			std::cout << "Enter First Name: ";
			std::cin >> fname;
			std::cout << "Enter Last Name: ";
			std::cin >> lname;
			std::cout << "Enter Hourly Rate: ";
			std::cin >> hourly_rate;
			std::cout << "Enter Hours Worked: ";
			std::cin >> hours_worked;

			example::Person new_person(id, fname, lname, hourly_rate, hours_worked);
			DB.add_person(new_person);

			std::cout << "Person added successfully\n";
			/*	try
			{
				DB.add_person(example::Person(42, "Bob", "Smith"));
			}
			catch (std::runtime_error e)
			{
				std::cout << "Error caught" << e.what() << "\n";
			}*/
		}

		else if (option == 2)	// Remove
		{
			int id;
			std::cout << "Enter ID to remove: ";
			std::cin >> id;

			if (DB.remove_person(id))
				std::cout << "Person removed.\n";
			else
				std::cout << "Person with ID " << id << " not found.\n";

		}
		else if (option == 3)	// Generate report
			std::cout << DB.to_string();
		else if (option == 4)	// Ending program
		{
			std::cout << "Quitting program...\n";
			break;
		}
		else
			std::cout << "Invalid number.\n";
	}

	return 0;
}