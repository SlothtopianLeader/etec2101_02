#pragma once
#include <sstream>
#include <ostream>
namespace ssuds
{
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @ ENUM CLASSES                           @
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	enum class LinkedListIteratorType {
		/// <summary>
		/// This LinkedLists iterator visits items from beginning to end
		/// </summary>
		FORWARD,

		/// <summary>
		/// This LinkedLists iterator visits items from end to beginning
		/// </summary>
		BACKWARDS
	};
	template <class T>
	class LinkedList
	{
	private:
		class Node
		{
		public:
			T mData;
			Node* mNext;
			Node* mPrevious;

			Node(const T& data) : mData(data), mNext(nullptr), mPrevious(nullptr) {}
		};
	public:
		class LinkedListIterator
		{
		private:
			unsigned int mCurrentIndex;
			LinkedListIterator* mLinkedListPtr;

			Node* mCurrentNode;

			/// <summary>
			/// Type of iterator
			/// </summary>
			LinkedListIteratorType mType;

		public:

			/// <summary>
			/// The main constructor
			/// </summary>
			/// <param name="startNode"></param>
			/// <param name="type"></param>
			LinkedListIterator(Node* startNode, LinkedListIteratorType type = LinkedListIteratorType::FORWARD)
			{
				mCurrentNode = startNode;
				mType = type;
			}

			Node* getNode() const
			{
				return mCurrentNode;
			}
			/// <summary>
			/// Are we not equal to the other iterator?  This is computed by inverting the result of the
			/// == operator
			/// </summary>
			/// <param name="other">The iterator we're comparing ourself to</param>
			/// <returns>true if we're NOT equal</returns>
			bool operator != (const LinkedListIterator& other)
			{
				return this->mCurrentNode != other.mCurrentNode;
			}

			/// <summary>
			/// Returns a reference to the current item in the ArrayList.  It is important that the
			/// user only call this method if the iterator is not in an invalid state (defined by being
			/// equal to end/rend)
			/// </summary>
			/// <returns>A reference to the current object</returns>
			T& operator*()
			{
				return mCurrentNode->mData;
			}

			/// <summary>
			/// Increments / advances the iterator (prefix ++x version).  This version of ++ returns
			/// a copy of the Iterator *after* the ++ is performed.  So if the user did this:
			/// y = ++x
			/// X is changed, and a copy is returned which can be assigned to y.
			/// It is the responsibility of the user to NOT call this if the iterator is 
			/// invalid (equal to end/rend) -- if they ignore this rule, the results are indeterminate.
			/// </summary>
			LinkedListIterator operator++()
			{
				//LinkedListIterator return_val(mLinkedListPtr, mType, mCurrentIndex);
				if (mType == LinkedListIteratorType::FORWARD)
				{
					mCurrentIndex++;
					mCurrentNode = mCurrentNode->mNext;
				}
				else
				{
					mCurrentIndex--;
					mCurrentNode = mCurrentNode->mPrevious;
				}
				//return return_val;
			}

			/// <summary>
			/// Returns a copy of this iterator that is some amount offset from the current position.
			/// The resulting index of that iterator is constratined to be within -1...mSize
			/// </summary>
			/// <param name="offset">The amount to offset this iterator (positive or negative)</param>
			/// <returns>A copy of this iterator with the given offset applied</returns>
			LinkedListIterator operator+(int offset) const
			{
				LinkedListIterator temp = *this;
				for (int i = 0; i < offset && temp.mCurrentNode != nullptr; ++i)
				{
					temp.mCurrentNode = temp.mCurrentNode->mNext;
				}
				return temp;
			}

			/// <summary>
			/// I don't think std::vector does this, but it is the inverse of the + operator and easy to add
			/// </summary>
			/// <param name="offset">The amount to offset this iterator by (inverted)</param>
			/// <returns>A copy of this iterator with the given offset</returns>
			LinkedListIterator operator-(int offset) const
			{
				return (*this) + (-offset);
			}

			/// <summary>
			/// Are we equal to the other iterator?  I'm currently not considering the ArrayListIterator type...
			/// I'm not sure if that's the right call or not.
			/// </summary>
			/// <param name="other">The iterator we're comparing ourself to</param>
			/// <returns>true if we're equal</returns>
			bool operator==(const LinkedListIterator& other) const
			{
				return mLinkedListPtr == other.mLinkedListPtr && mCurrentIndex == other.mCurrentIndex;
			}

			friend class LinkedList;
		};
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// @ ATTRIBUTES                              @
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	private:
		unsigned int mSize;
		Node* mStart;
		Node* mEnd;
	public:
		/// <summary>
		/// This is the linked list default constructor
		/// </summary>
		LinkedList()
		{
			mSize = 0;
			mStart = nullptr;
			mEnd = nullptr;
		}

		/// <summary>
		/// This is the copy constructor
		/// </summary>
		/// <param name="other"></param>
		LinkedList(const LinkedList& other) : mSize(0), mStart(nullptr), mEnd(nullptr)
		{
			Node* current_node = other.mStart;
			while (current_node != nullptr)
			{
				this->append(current_node->mData);
				current_node = current_node->mNext;
			}
		}

		/// <summary>
		/// This is the destructor
		/// </summary>
		~LinkedList()
		{
		}

		/// <summary>
		/// Inserts a new element at the end of the list
		/// </summary>
		/// <param name="val">the new value to add</param>
		void append(const T& val)
		{
			Node* newNode = new Node(val);
			if (mSize == 0)
			{
				// Case1: list is currently empty
				// ... make a new Node and initialize
				/*
				Node* new_node = new Node;
				new_node->mData = val;
				new_node->mNext = nullptr;
				new_node->mPrevious = nullptr;

				mStart = new_node;
				mEnd = new_node;
				mSize = 1;
				*/
				mStart = mEnd = newNode;
			}
			else
			{
				// Case2: list has at least one item
				// ... make a new Node and initialize
				/*
				Node* new_node = new Node;
				new_node->mData = val;
				new_node->mNext = nullptr;
				new_node->mPrevious = nullptr;

				// ... hook up to existing "stuff"
				mEnd->mNext = new_node;
				new_node->mPrevious = mEnd;
				mEnd = new_node;
				*/
				mEnd->mNext = newNode;
				newNode->mPrevious = mEnd;
				mEnd = newNode;
			}
			mSize++;
		}

		void prepend(const T& val)
		{
			Node* new_node = new Node(val);
			new_node->mData = val;
			if (mStart == nullptr)
				mStart = new_node;
			else
			{
				new_node->mNext = mStart;
				mStart->mPrevious = new_node;
				mStart = new_node;
			}
		}

		/// <summary>
		/// Returns a reference to the item at the given index.
		/// This method will raise a std::out_of_range exception if an invalid index is given.
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		T& at(const unsigned int index) const
		{
			if (index >= mSize)
				throw std::out_of_range("Invalid index (" + std::to_string(index) + ")");
			Node* current_node = mStart;
			for (unsigned int i = 0; i < index; ++i)
			{
				current_node = current_node->mNext;
			}
			return current_node->mData;
		}


		T& operator[](unsigned int index)
		{
			if (index >= mSize)
				throw std::out_of_range("Invalid index (" + std::to_string(index) + ")");
			// Loop to get to the proper node (ITERATING)
			// ... start at beginning
			Node* current_node = mStart;
			for (unsigned int i = 0; i < index; i++)
			{
				current_node = current_node->mNext;
			}
			return current_node->mData;
		}

		friend std::ostream& operator <<(std::ostream& os, const LinkedList& slist)
		{
			slist.output(os);
			return os;
		}

		/// <summary>
		/// Inserts a new data item at a given index
		/// </summary>
		/// <param name="val">the new value to insert</param>
		/// <param name="index">the index at which to insert (must be >= 0 and <= size) </param>
		void insert(const T& val, unsigned int index)
		{
			if (index > mSize)
			{
				throw std::out_of_range("Invalid index");
			}

			else if (index == mSize)
			{
				append(val);
				return;
			}

			Node* new_node = new Node{ val };

			if (index == 0)
			{
				new_node->mNext = mStart;
				if (mStart)
					mStart->mPrevious = new_node;
				mStart = new_node;
				if (mSize == 0)
					mEnd = new_node;
			}

			else
			{
				Node* current_node = mStart;
				for (unsigned int i = 0; i < index; i++)
				{
					current_node = current_node->mNext;
				}
				new_node->mNext = current_node;
				new_node->mPrevious = current_node->mPrevious;
				if (current_node->mPrevious)
				{
					current_node->mPrevious->mNext = new_node;
				}
				else
					mStart = new_node;
				current_node->mPrevious = new_node;
			}
			mSize++;
		}

		/// <summary>
		/// This basically does the same thing as the << operator (the syntax is a bit different).  I 
		/// chose to keep it to preserve backwards compatiability with <Lab3 code.
		/// </summary>
		/// <param name="os">The output stream (cout, fp, stringstring, etc.) to write to</param>
		void output(std::ostream& os)
		{
			os << "[";
			Node* ptr = mStart;
			while (ptr != nullptr)
			{
				os << ptr->mData;
				if (ptr->mNext != nullptr)
					os << ", ";
				ptr = ptr->mNext;
			}
			os << "]";
		}

		void clear()
		{
			Node* temp = mStart;
			while (temp != nullptr)
			{
				Node* tnext = temp->mNext;
				delete temp;
				temp = tnext;
			}
			mStart = mEnd = nullptr;
			mSize = 0;
		}

		/// <summary>
		/// Returns an forward LinkedListIterator "pointing" at the first element (if it exists).  If the
		/// LinkedListIterator is empty, this iterator will be equal to end.
		/// </summary>
		/// <returns>A forward iterator referring to the first value value</returns>
		LinkedListIterator begin() const
		{
			return LinkedListIterator(mStart, LinkedListIteratorType::FORWARD);
		}

		/// <summary>
		/// The name can be a bit mis-leading, but this iterator does NOT return an iterator referring
		/// to the LAST element.  Instead, it returns a special value that indicates this is an invalid
		/// iterator (or we're done forward-traversing)
		/// </summary>
		/// <returns>An "end" type iterator value</returns>
		LinkedListIterator end() const
		{
			return LinkedListIterator(nullptr, LinkedListIteratorType::FORWARD);
		}

		/// <summary>
		/// Finds the index of the first occurrence of the given value
		/// </summary>
		/// <param name="val">the value to search for</param>
		/// <param name="start_index">the index to start searching at</param>
		/// <returns></returns>
		int find(const T& val, const unsigned int start_index = 0) const
		{
			// Find method using index
			if (start_index < 0 || start_index >= mSize)
			{
				throw std::out_of_range("Index is out of bounds");
			}
			Node* current_node = mStart;
			for (unsigned int i = 0; i < start_index; ++i)
			{
				current_node = current_node->mNext;
			}
			return current_node->mData;
		}

		/// <summary>
		/// Like the find method above, but using iterators
		/// </summary>
		/// <param name="val">The value to search for</param>
		/// <param name="start">Either begin, rbegin, or some other iterator to initialize the search</param>
		/// <returns>And end iterator or rend/end iterator value if not found</returns>
		LinkedListIterator find(const T& val, const LinkedListIterator& start) const
		{
			if (start.mLinkedListPtr != this)
				throw std::runtime_error("iterator must be based on this LinkedList");

			LinkedListIterator temp = begin();
			LinkedListIterator ender;

			if (start.mType == LinkedListIteratorType::FORWARD)
				ender = end();
			else
				ender = rend();

			while (temp != ender)
			{
				if (*temp == val)
					return temp;
				++temp;
			}
			return temp;
		}

		/// <summary>
		/// Returns the size of the internal list (i.e.) how many things are being stored in the LinkedList
		/// </summary>
		/// <returns>the size of the LinkedList</returns>
		unsigned int size() const
		{
			return mSize;
		}

		/// <summary>
		/// Returns a backwards LinkedListIterator "pointing" at the last element (if it exists).  If the
		/// LinkedListIterator is empty, this iterator will be equal to rend.
		/// </summary>
		/// <returns>A backwards iterator referring to the last valid value</returns>
		LinkedListIterator rbegin() const
		{
			return LinkedListIterator(mEnd, LinkedListIteratorType::BACKWARDS);
		}

		/// <summary>
		/// Returns a special value indicating we're done iterating backwards or that this iterator is invalid
		/// </summary>
		/// <returns>A special end value for backwards iteration</returns>
		LinkedListIterator rend() const
		{
			return LinkedListIterator(nullptr, LinkedListIteratorType::BACKWARDS);
		}

		/// <summary>
		/// Removes a item at the given index
		/// </summary>
		/// <param name="index"></param>
		/// <returns>the item that was removed</returns>
		T removeByIndex(int index)
		{
			if (index >= mSize || index < 0)
				throw std::out_of_range("Index is out of bounds");
			Node* current_node = mStart;
			for (int i = 0; i < index; ++i)
			{
				current_node = current_node->mNext;
			}

			if (current_node->mPrevious)
			{
				current_node->mPrevious->mNext = current_node->mNext;
			}
			else
			{
				mStart = current_node->mNext;
			}

			if (current_node->mNext)
			{
				current_node->mNext->mPrevious = current_node->mPrevious;
			}
			else
			{
				mEnd = current_node->mPrevious;
			}
			delete current_node;
			mSize--;
		}

		/// <summary>
		/// Removes an item using an iterator
		/// </summary>
		/// <param name="pos"></param>
		/// <returns></returns>
		T removeByIterator(const LinkedListIterator& pos)
		{
			Node* removeNode = pos.getNode();
			if (!removeNode)
				throw std::runtime_error("Invalid iterator");
			T val = removeNode->mData;

			if (removeNode->mPrevious)
				removeNode->mPrevious->mNext = removeNode->mNext;
			else
				mStart = removeNode->mNext;

			if (removeNode->mNext)
				removeNode->mNext->mPrevious = removeNode->mPrevious;
			else
				mEnd = removeNode->mPrevious;

			delete removeNode;
			mSize--;
			return val;
		}
	};
}