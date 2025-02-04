// #pragma once			// does the same compiler guard as below
#ifndef _PERSON_DATABASE_H_		// "compiler guard" -- makes sure this
#define _PERSON_DATABASE_H_		//	 header filer (and the stuff within it...our
						//	 class declaration) is only seen once by the
						//	 compiler

#include <string>

// Make all methods of this class const-safe that can be.

namespace ssuds
{
	/// <summary>
	/// This ArrayList class is an example of OOP techniques.
	/// </summary>
	class ArrayList
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
		int index;

	public:
		// This is the CONSTRUCTOR -- a method that has no return type and MUST
		// have the same name as the class. This is a DEFAULT CONSTRUCTOR (no parameters)

		/// <summary>
		/// This is the DEFAULT CONSTRUCTOR (no parameters), sets id to -1 and names
		/// to ?
		/// </summary>
		ArrayList();

		// This is ANOTHER CONSTRUCTOR

		/// <summary>
		/// This is the non-default constructor -- mostly initializes all parameters
		/// based on arguments from the caller
		/// </summary>
		/// <param name="start_id">This is the id# for the new Person</param>
		/// <param name="start_fname">This is the first name for the new Person</param>
		/// <param name="start_lname">This is the last name for the new Person</param>
		ArrayList(int start_id, std::string start_fname, std::string start_lname, float start_rate, unsigned int start_hours);

		// This is the DESTRUCTOR. This is called when an instance is about to go "away",
		// This method gets called. It is unusual to call this manually. More often, it's
		// called when an instance goes out of scope (scope is where that variable is visible, or
		// is defined).  Do any kind of cleanup you wish.  Biggie: if you dynamically allocated
		// any memory, this is a good place to clean it up.
		~ArrayList();

		// This if a METHOD -- a function that all instances of the class can
		// use. This is a DECLARATION.
		const int append();
		const int prepend();
		const int insert();
		int at();
		std::string output();
		bool remove(unsigned int index);
		const bool remove_all(unsigned int index);
		const bool find(unsigned int index);

		// These are examples of GETTERS
		unsigned int size;
		unsigned int capacity;
	};
}
#endif