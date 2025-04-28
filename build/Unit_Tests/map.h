#pragma once
#include <ostream>
#include <iostream>
#include <optional>
#include <string>
#include <functional>
#include <utility>
#include "array_list_utility.h"

namespace ssuds 
{
	enum class States {
		EMPTY,
		USED,
		DELETED
	};

	template <class K, class V>
	class Map
	{
	private:
		class Pair
		{
		public:
			K mKey;
			V mValue;
		};

		Pair* mArray;
		States* mStates;
		unsigned int mCapacity;
		unsigned int mSize;

		void grow()
		{
			unsigned int mTempCapacity = mCapacity;
			mCapacity *= 2;
			Pair* mTempArray = mArray;
			States* mTempStateArray = mStates;

			mArray = new Pair[mCapacity];
			mStates = new States[mCapacity];
			for (unsigned int i = 0; i < mCapacity; ++i)
			{
				mStates[i] = States::EMPTY;
			}
			mSize = 0;

			for (unsigned int i = 0; i < mTempCapacity; ++i)
			{
				if (mTempStateArray[i] == States::USED)
				{
					(*this)[mTempArray[i].mKey] = mTempArray[i].mValue;
				}
			}

			delete[] mTempArray;
			delete[] mTempStateArray;
		}

	public:

		/// <summary>
		/// The Default constructor
		/// </summary>
		Map() : mSize(0), mCapacity(8)
		{
			mArray = new Pair[mCapacity];
			mStates = new States[mCapacity];
			for (unsigned int i = 0; i < mCapacity; i++)
				mStates[i] = States::EMPTY;
		};

		// Copy-constructor
		Map(const Map& other)
		{
			mCapacity = other.mCapacity;
			mSize = other.mSize;
			mArray = new Pair[mCapacity];
			mStates = new States[mCapacity];
			for (unsigned int i = 0; i < mCapacity; ++i)
			{
				mArray[i] = other.mArray[i];
				mStates[i] = other.mStates[i];
			}
		}

		// Move-constructor
		Map(Map&& other) : mArray(other.mArray), mStates(other.mStates), mCapacity(other.mCapacity), mSize(other.mSize)
		{
			other.mArray = nullptr;
			other.mStates = nullptr;
			other.mCapacity = 0;
			other.mSize = 0;
		}

		// Destructor
		~Map()
		{
			delete[] mArray;
			delete[] mStates;
		}
		
		/// <summary>
		/// This inserts or gets the value associated with the key
		/// </summary>
		/// <param name="the_key"></param>
		/// <returns></returns>
		V& operator[](const K& the_key)
		{
			int mIndex = hash(the_key);

			while (mStates[mIndex] == States::USED && mArray[mIndex].mKey != the_key)
			{
				mIndex = (mIndex + 1) % mCapacity;
			}

			if (mStates[mIndex] != States::USED)
			{
				mArray[mIndex].mKey = the_key;
				mArray[mIndex].mValue = V();
				mStates[mIndex] = States::USED;
				mSize++;
			}
			return mArray[mIndex].mValue;
		}

	private:
		int hash(const K& key)
		{
			std::hash<K> hasher;
			return hasher(key) % mCapacity;
		}

	public:

		// Capacity
		unsigned int capacity() const
		{
			return mCapacity;
		}

		/// <summary>
		/// This checks if a key exists in the map
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		bool contains(const K& key) const
		{
			std::hash<K> hasher;
			size_t index = hasher(key) % mCapacity;
			while (mStates[index] != States::EMPTY)
			{
				if (mStates[index] == States::USED && mArray[index].mKey == key)
					return true;
				index = (index + 1) % mCapacity;
			}
			return false;
		}

		/// <summary>
		/// This removes a key from the map
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		bool remove(const K& key)
		{
			std::hash<K> hasher;
			size_t index = hasher(key) % mCapacity;

			while (mStates[index] != States::EMPTY)
			{
				if (mStates[index] == States::USED && mArray[index].mKey == key)
				{
					mStates[index] = States::DELETED;
					--mSize;
					return true;
				}
				index = (index + 1) % mCapacity;
			}
			return false;
		}

		friend std::ostream& operator<<(std::ostream& os, const Map& map)
		{
			os << "{";
			bool first = true;
			for (unsigned int i = 0; i < map.mCapacity; ++i)
			{
				if (map.mStates[i] == States::USED)
				{
					if (!first)
						os << ", ";
					first = false;
					os << map.mArray[i].mKey << ":" << map.mArray[i].mValue;
				}
			}
			os << "}";
			return os;
		}
	};
}

