// person_database.cpp -- houses the BODIES (DEFINTIONS) of all methods
#include <person_database.h>
#include <iostream>

//int person_array_size = 0;
//General structure:	ReturnType ClassName::MethodName(PARAMETERS) { .... }
namespace example {
	void example::Person::add_person(example::Person new_person)
	{
		for (int i = 0; i < person_array_size; i++)
			person_array[i].some_method();		// change the some_method out, but don't switch it with add_person() :)

		for (int i = 0; i < person_array_size; i++)
		{
			if (person_array[i].get_id() == new_person.get_id())
			{
				std::string err_msg = "Duplicated id" + std::to_string(new_person.get_id());
				throw std::runtime_error(err_msg);
			}
		}

		Person* temp_person_array = new Person[person_array_size + 1];

		for (int i = 0; i < person_array_size; i++)		// This copies the data from the old array
			temp_person_array[i] = person_array[i];		//	to the new array.

		temp_person_array[person_array_size] = new_person;

		delete[] person_array;		// This frees the old array

		person_array = temp_person_array;
		person_array_size++;

	}
	void example::Person::remove_person(example::Person new_person)
	{
		for (int i = 0; i < person_array_size; i++)
		{
			if (person_array_size[i].get_id() == new_person.get_id())
			{
				remove_person();
				return true;
			}
			else
				return false;
		}
	}
	void example::Person::get_num_people(example::Person new_person)
	{
		int person_array_sum = 0;
		for (int i = 0; i < person_array_size; i++)
		{
			person_array_sum++;
		}
		std::cout << "Number of people in the database: " << person_array_sum << "\n";
	}
	void example::Person::to_string(example::Person new_person)
	{

	}
	example::PersonDatabase::PersonDatabase(std::string fname)
	{
		person_array = nullptr;

		while (true)
		{
			if (fp.eof())
				break;
			Person p(new_id, new_fname, new_lname);
			p.set_hourly_rate(new_rate);
			p.get_hours_worked(new_hours);
			add_person(p);
		}
	}
}