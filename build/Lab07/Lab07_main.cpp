#include <iostream>
#include <fstream>
#include <ostream>
#include "ordered_set.h"

int main(int argc, char** argv)
{
	ssuds::OrderedSet<float> fset;
	fset.insert(1.1f);
	fset.insert(2.2f);
	fset.insert(1.1f);		// no effect
	fset.insert(3.3f);
	fset.insert(0.5f);

	fset.insert(4.5f);
	fset.insert(4.8f);

	std::cout << fset.contains(3.3f) << "\n";		// true (1)
	std::cout << fset.contains(0.8f) << "\n";		// false (0)
	std::cout << fset.contains(4.5f) << "\n";		// true (1)


	//              1.1
	//              /  \
	//             0.5 2.2
	//                  \
	//                  3.3
	//					  \
	//					  4.5
	//						\
	//						4.8


	std::cout << fset.get_height() << "\n";	       // 5		
	
	auto parent = fset.get_parent(4.5f);			// 3.3
	if (parent.has_value())
		std::cout << "Parent: " << parent.value() << "\n";		// Parent: 3.3
	else
		std::cout << "Parent not found or it is the root.\n";
	
	void traversal_test();
	{
		std::cout << "\nTraversal Test\n================\n";
		ssuds::OrderedSet<float> set;
		set.insert(10.7f);
		set.insert(5.3f);
		set.insert(15.4f);
		set.insert(3.2f);
		set.insert(8.6f);
		
		ssuds::ArrayList<float> preOrder = set.traversal(ssuds::TraversalType::PREORDER);
		std::cout << "Pre-Order traversal: ";
		for (int i = 0; i < preOrder.size(); i++)
		{
			std::cout << preOrder[i] << " ";
		}
		std::cout << "\n";

		ssuds::ArrayList<float> inOrder = set.traversal(ssuds::TraversalType::INORDER);
		std::cout << "In-Order traversal: ";
		for (int i = 0; i < inOrder.size(); i++)
		{
			std::cout << inOrder[i] << " ";
		}
		std::cout << "\n";

		ssuds::ArrayList<float> postOrder = set.traversal(ssuds::TraversalType::POSTORDER);
		std::cout << "Post-Order traversal: ";
		for (int i = 0; i < postOrder.size(); i++)
		{
			std::cout << postOrder[i] << " ";
		}
	}
}