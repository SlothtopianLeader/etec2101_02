// #pragma once			// does the same compiler guard as below
#ifndef _PERSON_DATABASE_H_		// "compiler guard" -- makes sure this
#define _PERSON_DATABASE_H_		//	 header filer (and the stuff within it...our
						//	 class declaration) is only seen once by the
						//	 compiler

#include <string>
#include "person.h"


namespace example
{
	/// <summary>
	/// This Person class is an example of OOP techniques. Used for
	/// a couple projects (PeronDatabase) and as a test of a "complex"
	/// things (as opposed to int's, float's, strings)
	/// </summary>
	class PersonDatabase
	{
		// These are ATTRIBUTES -- variables that each instance of the class
		// gets a copy of.
		// By default all members of a class are PRIVATE (we can only
		//	 access them in a method). Normally we make our attributes private
		//	 but methods public.
	private:
		/// <summary>
		/// This is the (unique) ID# of this Person
		/// </summary>
		Person* person_array;

		/// <summary>
		/// This holds the amount of people we have in our array
		/// </summary>
		unsigned int person_array_size;
		std::string filename;

	public:

		/// <summary>
		/// This is the PersonDatabase constructor
		/// </summary>
		/// <param name="fname"></param>
		PersonDatabase(std::string fname);
		/// <summary>
		/// This is the PersonDatabase destructor
		/// </summary>
		~PersonDatabase();
		/// <summary>
		/// This adds a new Person to the database
		/// </summary>
		/// <param name="new_person"></param>
		void add_person(Person new_person);
		/// <summary>
		/// This removes a Person from the database
		/// </summary>
		/// <param name="id"></param>
		/// <returns></returns>
		bool remove_person(unsigned int id);
		/// <summary>
		/// This returns the amount of people within the database
		/// </summary>
		/// <returns></returns>
		int get_num_people();
		/// <summary>
		/// This returns a string, in this case our report
		/// </summary>
		/// <returns></returns>
		std::string to_string();
	};
}
#endif