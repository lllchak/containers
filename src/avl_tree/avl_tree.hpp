#ifndef AVL_TREE_HPP_
#define AVL_TREE_HPP_

#include <iostream>
#include <algorithm>

#include "avl_node.hpp"

#define S21_NOEXCEPT throw()

namespace s21 {
    template<class T, class Cmp = std::less<typename T::first_type>, class Allocator = std::allocator<T>>
    class AVLTree {
    public:
        using value_type = T;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference = value_type&;
        using node_alloc = typename Allocator::template rebind<s21::AVLNode<T>>::other;
        using pair_alloc = Allocator;

        using key = typename value_type::first_type;
        using value = typename value_type::second_type;

    public:
        AVLTree() : root_(nullptr), size_(0) {}
        // AVLTree(const AVLTree &src) {}               --- COPY CTOR

        bool empty() const S21_NOEXCEPT {
            return (size_ == 0);
        }

        size_type size() const S21_NOEXCEPT {
            return size_;
        }

        int height() const S21_NOEXCEPT {
            return (root_ == nullptr) ? 0 : (height(root_) - 1);
        }

        bool contains(key src) const S21_NOEXCEPT {
            return contains(root_, src);
        }
    
    private:
        int height(s21::AVLNode<value_type> *node) const S21_NOEXCEPT{
            if (node == nullptr) {
                return -1;
            }

            int left_height = height(node->left_) + 1;
            int right_height = height(node->right_) + 1;
            return std::max(left_height, right_height);
        }

        bool contains(s21::AVLNode<value_type> *node, key src) const S21_NOEXCEPT {
            if (node == nullptr) {
                return false;
            }

            bool right_comp = comp_(node.data_.first, src);
            bool left_comp = comp_(src, node->data_.right, src);

            if (!right_comp && !left_comp) {
                return true;
            } else if (!right_comp) {
                return (contains(node->left_, src));
            } else if (!left_comp) {
                return (contains(node->right_, src));
            }
            
        }


    private:
        s21::AVLNode<value_type> *root_;
        size_type size_;
        node_alloc n_alloc;
        pair_alloc p_alloc;
        Cmp comp_;


    };
}

#endif 