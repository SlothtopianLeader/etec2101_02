// #pragma once			// does the same compiler guard as below
#ifndef _PERSON_H_		// "compiler guard" -- makes sure this
#define _PERSON_H_		//	 header filer (and the stuff within it...our
						//	 class declaration) is only seen once by the
						//	 compiler

#include <string>

namespace example
{
	/// <summary>
	/// This Person class is an example of OOP techniques. Used for
	/// a couple projects (PeronDatabase) and as a test of a "complex"
	/// things (as opposed to int's, float's, strings)
	/// </summary>
	class Person
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
		int id;
		std::string first_name;
		std::string last_name;
		float hourly_rate;
		unsigned int hours_worked;

	public:
		// This is the CONSTRUCTOR -- a method that has no return type and MUST
		// have the same name as the class. This is a DEFAULT CONSTRUCTOR (no parameters)
		
		/// <summary>
		/// This is the DEFAULT CONSTRUCTOR (no parameters), sets id to -1 and names
		/// to ?
		/// </summary>
		Person();

		// This is ANOTHER CONSTRUCTOR

		/// <summary>
		/// This is the non-default constructor -- mostly initializes all parameters
		/// based on arguments from the caller
		/// </summary>
		/// <param name="start_id">This is the id# for the new Person</param>
		/// <param name="start_fname">This is the first name for the new Person</param>
		/// <param name="start_lname">This is the last name for the new Person</param>
		Person(int start_id, std::string start_fname, std::string start_lname, float start_rate, unsigned int start_hours);

		// This is the DESTRUCTOR. This is called when an instance is about to go "away",
		// This method gets called. It is unusual to call this manually. More often, it's
		// called when an instance goes out of scope (scope is where that variable is visible, or
		// is defined).  Do any kind of cleanup you wish.  Biggie: if you dynamically allocated
		// any memory, this is a good place to clean it up.
		~Person();

		// This if a METHOD -- a function that all instances of the class can
		// use. This is a DECLARATION.
		float calculate_pay();

		// These are examples of SETTERS
		void set_hourly_rate(float new_rate);
		void set_hours_worked(unsigned int new_hours);

		// These are examples of GETTERS
		int get_id();
		std::string get_first_name();
		std::string get_last_name();
		unsigned int get_hours_worked();
		float get_hourly_rate();
	};
}
#endif
