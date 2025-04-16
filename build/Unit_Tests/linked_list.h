#pragma once
#include <sstream>
#include <ostream>
namespace ssuds
{
	enum class LinkedListIteratorType {
		FORWARD,
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
		};
	public:
		class LinkedListIterator
		{
		private:
			unsigned int mCurrentIndex;
			LinkedListIterator* mLinkedListPtr;

			Node* mCurrentNode;

			LinkedListIteratorType mType;

		public:
			LinkedListIterator(Node* startNode, LinkedListIteratorType type = LinkedListIteratorType::FORWARD)
			{
				mCurrentNode = startNode;
				mType = type;
			}
			Node* getNode() const
			{
				return mCurrentNode;
			}
			bool operator != (const LinkedListIterator& other)
			{
				return this->mCurrentNode != other.mCurrentNode;
			}
			T& operator*()
			{
				return mCurrentNode->mData;
			}
			void operator++()
			{
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
			}

			LinkedListIterator operator+(int offset) const
			{
				LinkedListIterator temp = *this;
				for (int i = 0; i < offset && temp.mCurrentNode != nullptr; ++i)
				{
					temp.mCurrentNode = temp.mCurrentNode->mNext;
				}
				return temp;
			}

			LinkedListIterator operator-(int offset) const
			{
				return (*this) + (-offset);
			}

			bool operator==(const LinkedListIterator& other) const
			{
				return mLinkedListPtr == other.mLinkedListPtr && mCurrentIndex == other.mCurrentIndex;
			}

			friend class LinkedList;
		};
	private:
		unsigned int mSize;
		Node* mStart;
		Node* mEnd;
	public:
		// default constructor
		LinkedList()
		{
			mSize = 0;
			mStart = nullptr;
			mEnd = nullptr;
		}

		// copy constructor
		LinkedList(const LinkedList& other) : mSize(0), mStart(nullptr), mEnd(nullptr)
		{
			Node* current_node = other.mStart;
			while (current_node != nullptr)
			{
				this->append(current_node->mData);
				current_node = current_node->mNext;
			}
		}

		// Destructor
		~LinkedList()
		{
		}
	
		void append(const T& val)
		{
			if (mSize == 0)
			{
				// Case1: list is currently empty
				// ... make a new Node and initialize
				Node* new_node = new Node;
				new_node->mData = val;
				new_node->mNext = nullptr;
				new_node->mPrevious = nullptr;

				mStart = new_node;
				mEnd = new_node;
				mSize = 1;
			}
			else
			{
				// Case2: list has at least one item
				// ... make a new Node and initialize
				Node* new_node = new Node;
				new_node->mData = val;
				new_node->mNext = nullptr;
				new_node->mPrevious = nullptr;

				// ... hook up to existing "stuff"
				mEnd->mNext = new_node;
				new_node->mPrevious = mEnd;
				mEnd = new_node;

				mSize++;
			}
		}

		void prepend(const T& val)
		{
			Node* new_node = new Node;
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

		void insert(const T& val, unsigned int index)
		{
			if (index > mSize)
			{
				throw std::out_of_range("Invalid index");
			}

			Node* new_node = new Node{ val, nullptr, nullptr };

			if (index == 0)			// Beginning
			{
				new_node->mNext = mStart;
				if (mStart)
					mStart->mPrevious = new_node;
				mStart = new_node;
				if (mSize == 0)
					mEnd = new_node;
			}

			else if (index == mSize)		// End
			{
				append(val);
				return;
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
				current_node->mPrevious = new_node;
			}
			mSize++;
		}

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

		LinkedListIterator begin() const
		{
			return LinkedListIterator(mStart, LinkedListIteratorType::FORWARD);
		}

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

		unsigned int size() const
		{
			return mSize;
		}

		LinkedListIterator rbegin() const
		{
			return LinkedListIterator(mEnd, LinkedListIteratorType::BACKWARDS);
		}

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