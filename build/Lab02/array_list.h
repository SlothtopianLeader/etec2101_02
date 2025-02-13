#ifndef _ARRAY_LIST_H_
#define _ARRAY_LIST_H_

#include <string>

/*
References:
https://www.geeksforgeeks.org/templates-cpp/
https://www.geeksforgeeks.org/references-in-cpp/
https://www.tutorialspoint.com/cplusplus/cpp_references.htm
*/
// Make all methods of this class const-safe that can be.

namespace ssuds
{
	template <class T>

	/// <summary>
	/// This ArrayList class is an example of OOP techniques.
	/// </summary>
	class ArrayList
	{

	private:
		/// <summary>
		/// This is the (unique) ID# of this Person
		/// </summary>
		T* mArray;
		unsigned int mArray_capacity;
		unsigned int mArray_size;


	public:
		/// <summary>
		/// This is the DEFAULT CONSTRUCTOR (no parameters), sets id to -1 and names
		/// to ?
		/// </summary>
		ArrayList() : mArray_capacity(5), mArray_size(0)
		{
			mArray = new T[mArray_capacity];
		}

		

		// This is ANOTHER CONSTRUCTOR

		/// <summary>
		/// This is the non-default constructor -- mostly initializes all parameters
		/// based on arguments from the caller
		/// </summary>
		/// <param name="start_id">This is the id# for the new Person</param>
		/// <param name="start_fname">This is the first name for the new Person</param>
		/// <param name="start_lname">This is the last name for the new Person</param>
		
		ArrayList(unsigned int capacity) : mArray_capacity(capacity), mArray_size(0)
		{
			mArray = new T[mArray_capacity];
		}

		/// <summary>
		/// This is the array list destructor, which frees the array.
		/// </summary>
		~ArrayList()
		{
			delete[]mArray;
		}

		/// <summary>
		/// This is the method will "reserve" space for the
		/// items that are to be added.
		/// </summary>
		/// <param name="newCapacity"></param>
		void reserve(unsigned int newCapacity)
		{
			if (newCapacity <= mArray_capacity)
				return;

			T* newArray = new T[newCapacity];

			for (unsigned int i = 0; i < mArray_size; i++)
			{
				newArray[i] = mArray[i];
			}

			delete[] mArray;
			mArray = newArray;

			mArray_capacity = newCapacity;
		}

		/// <summary>
		/// This is the append method which adds a new item to the
		/// end of the Array List.
		/// </summary>
		/// <param name="item"></param>
		void append(const T& item)
		{
			if (mArray_size == mArray_capacity)
			{
				reserve(mArray_capacity * 2);
			}

			mArray[mArray_size] = item;
			++mArray_size;
		}

		/// <summary>
		/// This is the prepend method which adds a new item
		/// to the beginning of the array list.
		/// </summary>
		/// <param name="item"></param>
		void prepend(const T& item)
		{
			if (mArray_size == mArray_capacity)
			{
				reserve(mArray_capacity * 2);
			}

			for (unsigned int i = mArray_size; i > 0; --i)
			{
				mArray[i] = mArray[i - 1];
			}

			mArray[0] = item;
			++mArray_size;
		}

		/// <summary>
		/// This is the insert method which takes the desired
		/// index and will move the items in the array list to
		/// make room for the new item.
		/// </summary>
		/// <param name="index"></param>
		/// <param name="item"></param>
		void insert(unsigned int index, const T& item)
		{
			if (index > mArray_size)
				throw std::out_of_range("Invalid Index.");

			if (mArray_size == mArray_capacity)
				reserve(mArray_capacity * 2);

			for (unsigned int i = mArray_size; i > index; --i)
				mArray[i] = mArray[i - 1];

			mArray[index] = item;
			++mArray_size;
		}

		/// <summary>
		/// This is the at method which takes an index and
		/// it returns a refernece to the item at that spot.
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		T& at(unsigned int index) const
		{
			if (index >= mArray_size)
				throw std::out_of_range("Invalid Index.");
			
			return mArray[index];
		}

		/// <summary>
		/// This is the output method which takes a reference to
		/// the std::ostream object.
		/// </summary>
		/// <param name="os"></param>
		void output(std::ostream& os) const
		{
			os << "[";
			for (unsigned int i = 0; i < mArray_size; ++i)
			{
				if (i > 0)
					os << ", ";
				os << mArray[i];
			}
			os << "]";
		}

		/// <summary>
		/// This is the remove method which takes an 
		/// index and removes the item at that spot.
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		T remove(unsigned int index)
		{
			if (index >= mArray_size)
				throw std::out_of_range("Invalid Index");

			T removedItem = mArray[index];

			for (unsigned int i = index; i < mArray_size - 1; ++i)
			{
				mArray[i] = mArray[i + 1];
			}
			--mArray_size;

			if (mArray_size <= mArray_capacity / 4)
				reserve(mArray_capacity / 2);

			return removedItem;
		}

		/// <summary>
		/// This is a remove_all method that takes a value,
		/// and removes all occurences, and returns the number
		/// of occurences removed.
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		unsigned int remove_all(const T& value)
		{
			unsigned int count = 0;

			for (unsigned int i = 0; i < mArray_size;)
			{
				if (mArray[i] == value)
				{
					remove(i);
					++count;
				}
				else
					++i;
			}
			return count;
		}

		/// <summary>
		/// This is the find method which takes an reference
		/// to a value to find and the starting index. This returns
		/// the index of the first occurrence of the value, or
		/// after the given starting index.
		/// </summary>
		/// <param name="value"></param>
		/// <param name="startIndex"></param>
		/// <returns></returns>
		int find(const T& value, unsigned int startIndex = 0) const
		{
			if (startIndex >= mArray_size)
				return -1;
			for (unsigned int i = startIndex; i < mArray_size; ++i)
			{
				if (mArray[i] == value)
				{
					return i;
				}
			}
			return -1;
		}


		/// <summary>
		/// This is a Getter method that returns the array size.
		/// </summary>
		/// <returns></returns>
		unsigned int size() const
		{
			return mArray_size;
		}
		/// <summary>
		/// This is another Getter method that returns the array capacity.
		/// </summary>
		/// <returns></returns>
		unsigned int capacity() const
		{
			return mArray_capacity;
		}
	};
}

#endif