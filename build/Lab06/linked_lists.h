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
		};
	private:
		unsigned int mSize;
		Node* mStart;
		Node* mEnd;
	public:
		LinkedList()
		{
			mSize = 0;
			mStart = nullptr;
			mEnd = nullptr;
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

		void insert(const T& val, unsigned int index)
		{
			if (index > mSize)
			{
				throw std::out_of_range("Invalid index");
			}

			if (index == 0)			// Beginning
			{
				Node* new_node = new Node;
				new_node->mData = val;
				new_node->mPrevious = nullptr;
				new_node->mNext = mStart;

				if (mStart != nullptr)
					mEnd = new_node;
				mSize++;
				return;
			}

			if (index == mSize)		// End
			{
				append(val);
				return;
			}
			Node* current_node = mStart;
			for (unsigned int i = 0; i < index; i++)
			{
				current_node = current_node->mNext;
			}

			Node* new_node = new Node;
			new_node->mData = val;

			new_node->mPrevious = current_node->mPrevious;
			new_node->mNext = current_node;
			current_node->mPrevious->mNext = new_node;
			current_node->mPrevious = new_node;

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
			// Add some more
			// Note that once you finish clear method
			// ... you can call it in the destructor.
		}
		LinkedListIterator begin() const
		{
			return LinkedListIterator(mStart, LinkedListIteratorType::FORWARD);
		}

		LinkedListIterator end() const
		{
			return LinkedListIterator(nullptr, LinkedListIteratorType::FORWARD);
		}

		int find(const T& val, const unsigned int start_index = 0) const
		{
			// Find method using index
		}

		LinkedListIterator find(const T& val, const LinkedListIterator& start) const
		{
			// Find method using iterator
		}

		unsigned int size() const
		{
			return mSize;
		}
	};
}