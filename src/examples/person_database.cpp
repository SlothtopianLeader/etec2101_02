// person_database.cpp -- houses the BODIES (DEFINTIONS) of all methods
#include <person_database.h>
#include <iostream>

int person_array_size = 0;
//General structure:	ReturnType ClassName::MethodName(PARAMETERS) { .... }

void example::Person::add_person(example::Person new_person)
{
	for (int i = 0; i < person_array_size; i++)
	{
		if(*(person_array + i))
			if (person_array[i].get_id() == new_person.get_id())
			{
				std::string err_msg = "Duplicated id" + std::to_string(new_person.get_id());
				throw std::runtime_error(err_msg);
			}
	}
}

void example::Person::set_hourly_rate(float new_rate)
{
	// Imagine that we COULD do data validation rules to make sure new_rate
	// makes sense (according to company policy) before assigning it.
	// We can also set breakpoints here to DETECT any time a change is made.
	hourly_rate = new_rate;
}

void example::Person::set_hours_worked(unsigned int new_hours)
{
	hours_worked = new_hours;
}

int example::Person::get_id()
{
	return id;
}

std::string example::Person::get_first_name()
{
	return first_name;
}

std::string example::Person::get_last_name()
{
	return last_name;
}

float example::Person::get_hourly_rate()
{
	return hourly_rate;
}

unsigned int example::Person::get_hours_worked()
{
	return hours_worked;
}

example::Person::Person()
{
	id = -1;
	first_name = "?";
	last_name = "?";
	hours_worked = 0;
	hourly_rate = 0.0f;
}

example::Person::Person(int start_id, std::string start_fname, std::string start_lname)
{
	id = start_id;
	first_name = start_fname;
	last_name = start_lname;
	hours_worked = 0;
	hourly_rate = 0.0f;
}

example::Person::~Person()
{
	std::cout << "The person named " << first_name << " " << last_name << " is about to go away.\n";
}