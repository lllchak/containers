#include <iostream>

#include "avl_node.hpp"
#include "avl_tree.hpp"

using namespace s21;

int main() {
	AVLTree<std::pair<int, int>> tree;
	tree.insert(std::make_pair(125, 118));
	tree.insert(std::make_pair(3, 4));
	tree.insert(std::make_pair(5, 6));
	tree.insert(std::make_pair(7, 8));
	tree.insert(std::make_pair(9, 10));
	tree.insert(std::make_pair(11, 12));

	tree.print();

	std::cout << "\n\n\n\n" << tree.empty() << " " << tree.size() << " " << tree.height() << "\n\n\n\n";
	tree.delete_tree();
	return 0;
}
