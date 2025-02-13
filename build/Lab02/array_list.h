#include <string>

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

		~ArrayList()
		{
			delete[]mArray;
		}


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

		void append(const T& item)
		{
			if (mArray_size == mArray_capacity)
			{
				reserve(mArray_capacity * 2);
			}

			mArray[mArray_size] = item;
			++mArray_size;
		}

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

		T& at(unsigned int index) const
		{
			if (index >= mArray_size)
				throw std::out_of_range("Invalid Index.");
			
			return mArray[index];
		}
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



		// These are examples of GETTERS
		unsigned int size() const
		{
			return mArray_size;
		}
		unsigned int capacity() const
		{
			return mArray_capacity;
		}
	};
}