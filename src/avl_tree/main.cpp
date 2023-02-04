#include <iostream>

#include "avl_node.hpp"
#include "avl_tree.hpp"

using namespace s21;

int main() {
	AVLTree<std::pair<AVLNode<int>, int>> tree;
	std::cout << tree.empty();
	std::cout << tree.size();
	std::cout << tree.height();
	return 0;
}
