#pragma once
#include <ostream>
#include <iostream>
#include <optional>
#include <string>
#include <string>
#include "array_list_utility.h"

namespace ssuds
{
	enum class TraversalType {
		PREORDER,
		POSTORDER,
		INORDER
	};
	template <class T>
	class OrderedSet
	{
	private:
		class Node
		{
		private:
			T mData;
			Node* mLeft;
			Node* mRight;
		public:
			Node(const T& data) : mData(data), mLeft(nullptr), mRight(nullptr)
			{
				// empty, on purpose
			}

			std::optional<T> get_parent_recursive(Node* current_node, const T& val) const
			{
				if (current_node == nullptr)
					return std::nullopt;

				if (current_node->mLeft != nullptr && current_node->mLeft->mData == val)
					return current_node->mData;

				if (current_node->mRight != nullptr && current_node->mRight->mData == val)
					return current_node->mData;

				if (val < current_node->mData)
					return get_parent_recursive(current_node->mLeft, val);
				else
					return get_parent_recursive(current_node->mRight, val);
			}

			bool insert_recursive(const T& val)
			{
				if (mData == val)
				{
					// A duplicate!
					return false;
				}
				else if (val < mData)
				{
					/// This value would go to our left
					if (mLeft == nullptr)
					{
						// I don't have a left child -- add one!
						mLeft = new Node(val);
						return true;
					}
					else
					{
						// I already have a left child -- let it handle the rest
						return mLeft->insert_recursive(val);
					}
				}
				else
				{
					// This value would go to our right
					// ....
					if (mRight == nullptr)
					{
						mRight = new Node(val);
						return true;
					}
					else
					{
						return mRight->insert_recursive(val);
					}
				}
			}

			bool contains_recursive(const T& value) const
			{
				// If I hold the value, return True
				// Else if the value is to left, return ....
				// Else, return ...

				if (value == mData)
					return true;
				else if (mData < value)
				{
					// if the node's value is < val, go right
					if (mRight == nullptr)
						return false;
					else
						return mRight->contains_recursive(value);

				}
				else
				{
					// else go left
					if (mLeft == nullptr)
						return false;
					else
						return mLeft->contains_recursive(value);
				}
			}

			Node* erase_recursive(const T& val)
			{
				if (val == mData)
				{
					// need to remove (and we now know we
					// need to return true
					if (!mLeft && !mRight)
					{
						delete this;
						return nullptr;
					}
					else if (mLeft && mRight)
					{
						// Case III
						Node* succ_parent = this;
						Node* succ = mRight;
						while (succ->mLeft != nullptr)
						{
							succ_parent = succ;
							succ = succ->mLeft;
						}

						mData = succ->mData;
						if (succ_parent == this)
							mRight = succ->mRight;
						else
							succ_parent->mLeft = succ->mRight;
						delete succ;
					}
					else if (mLeft && !mRight)
					{
						Node* temp = mLeft;
						mLeft = nullptr;
						delete this;
						return temp;
					}
					else    // !mLeft && mRight
					{
						Node* temp = mRight;
						mRight = nullptr;
						delete this;
						return temp;
					}
				}
				else if (val < mData && mLeft != nullptr)
				{
					mLeft = mLeft->erase_recursive(val);
				}
				else if (val > mData && mRight)
				{
					mRight = mRight->erase_recursive(val);
				}
				return this;
			}

			unsigned int get_height_recursive() const
			{
				unsigned int lHeight = 0;
				unsigned int rHeight = 0;

				if (mLeft != nullptr)
					lHeight = mLeft->get_height_recursive();
				if (mRight != nullptr)
					rHeight = mRight->get_height_recursive();
				if (lHeight > rHeight)
					return lHeight + 1;
				else
					return rHeight + 1;

			}

			void traversal_recursive(TraversalType t, ArrayList<T>& a) const
			{
				if (t == TraversalType::PREORDER)
				{
					a.append(mData);
					if (mLeft)
						mLeft->traversal_recursive(t, a);
					if (mRight)
						mRight->traversal_recursive(t, a);
				}

				else if (t == TraversalType::INORDER)
				{
					if (mLeft)
						mLeft->traversal_recursive(t, a);
					a.append(mData);
					if (mRight)
						mRight->traversal_recursive(t, a);
				}

				else if (t == TraversalType::POSTORDER)
				{
					if (mLeft)
						mLeft->traversal_recursive(t, a);
					if (mRight)
						mRight->traversal_recursive(t, a);
					a.append(mData);
				}
			}
			friend class OrderedSetIterator;
			friend class OrderedSet;
		};		// end of node class
		// Attributes of the OrderedSet class
		// height (can be computed from a method, so maybe not?)
		unsigned int mSize;
		Node* mRoot;

	public:
		OrderedSet() : mSize(0), mRoot(nullptr)
		{
			// empty, on purpose
		}

		// Return true if we actually added a new value
		bool insert(const T& new_val)
		{
			if (mSize == 0)
			{
				// This new value will be the root
				mRoot = new Node(new_val);
				mSize = 1;
				return true;
			}
			else
			{
				// We already have a root -- IT will add the data below if not a duplicate
				bool result = mRoot->insert_recursive(new_val);
				if (result)
					mSize++;
				return result;
			}
		}

		void clear()
		{
			if (mRoot != nullptr)
			{
				clear_recursive(mRoot);
				mRoot = nullptr;
				mSize = 0;
			}
		}

	private:

		void clear_recursive(Node* current_node)
		{
			if (current_node->mLeft != nullptr)
				clear_recursive(current_node->mLeft);
			if (current_node->mRight != nullptr)
				clear_recursive(current_node->mRight);
			delete current_node;
		}

	public:

		bool contains(const T& value) const
		{
			if (mSize == 0)
				return false;
			else
				return mRoot->contains_recursive(value);
		}

		bool erase(const T& val)
		{
			if (mSize == 0)
				return false;
			else
			{
				mRoot = mRoot->erase_recursive(val);
				mSize--;
				return true;
			}
		}

		unsigned int get_height() const
		{
			if (mSize == 0)
				return 0;
			else
				return mRoot->get_height_recursive();
		}

		void rebalance()
		{
			ssuds::ArrayList<T> io = traversal(ssuds::TraversalType::INORDER);
			clear();
			mRoot= rebalance_recursive(io, 0, io.size() - 1);
			mSize = io.size();
		}

	private:
		
		Node* rebalance_recursive(const ssuds::ArrayList<T>& a, int start, int end)
		{
			if (start > end)
				return nullptr;
			int mid = (start + end) / 2;
			Node* new_node = new Node(a[mid]);
			new_node->mLeft = rebalance_recursive(a, start, mid - 1);
			new_node->mRight = rebalance_recursive(a, mid + 1, end);

			return new_node;
		}

	public:
		std::optional<T> get_parent(const T& val) const
		{
			if (mRoot == nullptr)
				return std::nullopt;
			else
				return mRoot->get_parent_recursive(mRoot, val);
		}

		ArrayList<T> traversal(TraversalType t)
		{
			ArrayList<T> result;
			if (mRoot)
				mRoot->traversal_recursive(t, result);
			return result;
		}

		class OrderedSetIterator
		{
		private:
			ArrayList<Node*> stack;
			Node* current;

			void lPush(Node* current_node)
			{
				while (current_node != nullptr)
				{
					stack.append(current_node);
					current_node = current_node->mLeft;
				}
			}
		public:
			OrderedSetIterator(Node* root)
			{
				lPush(root);
				current = (stack.size() > 0) ? stack[stack.size() - 1] : nullptr;
			}

			OrderedSetIterator& operator++()
			{
				if (stack.size() == 0)
				{
					current = nullptr;
					return *this;
				}

				Node* node = stack[stack.size() - 1];
				stack.remove(stack.size() - 1);

				if (node->mRight != nullptr)
					lPush(node->mRight);
				current = (stack.size() > 0) ? stack[stack.size() - 1] : nullptr;
				return *this;
			}

			T& operator*() const
			{
				return current->mData;
			}

			bool operator!=(const OrderedSetIterator& other) const
			{
				return current != other.current;
			}

			bool operator==(const OrderedSetIterator& other) const
			{
				return current == other.current;
			}
		};

		OrderedSetIterator begin() const
		{
			return OrderedSetIterator(mRoot);
		}

		OrderedSetIterator end() const
		{
			return OrderedSetIterator(nullptr);
		}
	};
}