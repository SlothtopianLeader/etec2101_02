// person_database.cpp -- houses the BODIES (DEFINTIONS) of all methods
#include "person_database.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

//int person_array_size = 0;
//General structure:	ReturnType ClassName::MethodName(PARAMETERS) { .... }
namespace example {
	PersonDatabase::PersonDatabase(std::string fname) {
		std::ifstream file(fname);
		if (!file.is_open()) {
			std::cout << "File not found: " << fname << "\n";
			person_array = nullptr;
			person_array_size = 0;
			return;
		}

		person_array_size = 0;
		person_array = nullptr;

		std::string line;
		while (std::getline(file, line)) {
			std::stringstream ss(line);
			int id;
			std::string fname, lname;
			float rate;
			unsigned int hours;

			ss >> id >> fname >> lname >> rate >> hours;
			add_person(Person(id, fname, lname, hours, rate));
		}

		file.close();
	}

	PersonDatabase::~PersonDatabase()
	{
		std::ofstream file("..\\..\\media\\person_database.txt");
		if (!file.is_open())
		{
			std::cout << "Error saving file!\n";
			return;
		}
		for (unsigned int i = 0; i < person_array_size; i++)
		{
			file << person_array[i].get_id() << " "
				<< person_array[i].get_first_name() << " "
				<< person_array[i].get_last_name() << " "
				<< person_array[i].get_hourly_rate() << " "
				<< person_array[i].get_hours_worked() << "\n";
		}
		file.close();
		delete[] person_array;
	}

	void PersonDatabase::add_person(Person new_person)
	{
		for (unsigned int i = 0; i < person_array_size; i++)
		{
			if (person_array[i].get_id() == new_person.get_id())
				throw std::runtime_error("Error: Duplicate ID. Please enter a valid ID.");
		}
		Person* new_array = new Person[person_array_size + 1];

		for (unsigned int i = 0; i < person_array_size; i++)
			new_array[i] = person_array[i];

		new_array[person_array_size] = new_person;

		delete[] person_array;
		person_array = new_array;
		person_array_size++;
	}
	bool PersonDatabase::remove_person(unsigned int id)
	{
		int index = -1;
		for (unsigned int i = 0; i < person_array_size; i++)
		{
			if (person_array_size[i].get_id() == id)
			{
				index = i;
				break;
			}
		}
		if (index == -1)
			return false;	// person don't exist

		// This creates a new array with one less size
		Person* temp_person_array = new Person[person_array_size - 1];

		// This copies all information except the removed person
		for (unsigned int i = 0, j = 0; i < person_array_size; i++)
		{
			if (i != index)
				temp_person_array[j++] = person_array[i];
		}
		delete[] person_array;
		person_array = temp_person_array;
		person_array_size--;

		return true;
	}
	int PersonDatabase::get_num_people()
	{
		return person_array_size;
	}

	/* Reference: https://cplusplus.com/reference/sstream/stringstream/stringstream/ */
	std::string PersonDatabase::to_string()
	{
		std::stringstream ss;
		ss << "Person ID	Hours	Rate	Monthly Salary\n";
		ss << "=========	=====	====	==============\n";

		float total_salary = 0.0;
		for (unsigned int i = 0; i < person_array_size; i++)
		{
			float salary = person_array[i].calculate_pay();
			total_salary += salary;

			ss << person_array[i].get_first_name() << " " << person_array[i].get_last_name() << " "
				<< person_array[i].get_id() << " "
				<< person_array[i].get_hours_worked() << " "
				<< "$" << person_array[i].get_hourly_rate() << " "
				<< "$" << salary << "\n";
		}
		ss << "==========================================\n";
		ss << "Total: $" << total_salary << "\n";

		return std::string();
	}
}