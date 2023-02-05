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

        using key = typename value_type::first_type;
        using value = typename value_type::second_type;

    public:
        AVLTree() : root_(nullptr), size_(0) {}
        // AVLTree(const AVLTree &src) {}               --- COPY CTOR
        ~AVLTree() {}

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

        void delete_node(s21::AVLNode<value_type> *node) {
            n_alloc.deallocate(node, 1);
            node = NULL;
        }

        s21::AVLNode<value_type> *delete_subtree(s21::AVLNode<value_type> *node) {
            if (node != nullptr) {
                delete_subtree(node->left_);
                delete_subtree(node->right_);
                delete_node(node);
            }

            return nullptr;
        }

        void delete_tree() {
            root_ = delete_subtree(root_);
            size_ = 0;
        }

        s21::AVLNode<value_type> *create_node(value_type src) {
            s21::AVLNode<value_type>* node = n_alloc.allocate(1);
            n_alloc.construct(node, src);
            return node;
        }

        bool insert(value_type src) {
            if (!contains(root_, src.first)) {
                root_ = insert(root_, src);
                root_->parent_ = nullptr; size_++;
                return true;
            }

            return false;
        }

////shiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiit

        void print_help(s21::AVLNode<value_type> *node, int space) {
            if (node == nullptr) {
                return;
            }

            space += 10;

            print_help(node->right_, space);
            std::cout << "\n";
            for (int i = 0; i < space; i++) {
                std::cout << " ";
            }
            std::cout << node->data_.first << " " << node->data_.second << "\n";

            print_help(node->left_, space);
        }

        void print() {
            print_help(root_, 0);
        }
    
    private:
        int height(s21::AVLNode<value_type> *node) const S21_NOEXCEPT {
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

            bool right_comp = comp_(src, node->data_.first);
            bool left_comp = comp_(node->data_.first, src);

            if (!right_comp && !left_comp) {
                return true;
            } else if (!right_comp) {
                return (contains(node->left_, src));
            } else if (!left_comp) {
                return (contains(node->right_, src));
            }

            return true;
        }

        s21::AVLNode<value_type>* insert(s21::AVLNode<value_type> *node, value_type src) S21_NOEXCEPT {
            if (node == nullptr) {
                return create_node(src);
            }

            bool cmp_result = comp_(src.first, node->data_.first);
            if (cmp_result) {
                node->left_ = insert(node->left_, src);
                node->left_->parent_ = node;
            } else if (!cmp_result) {
                node->right_ = insert(node->right_, src);
                node->right_->parent_ = node;
            }

            node_update(node);
            return(balance(node));
        }

        void node_update(s21::AVLNode<value_type> *node) S21_NOEXCEPT {
            int left_height = (node->left_ == nullptr) ? -1 : node->left_->height_;
            int right_height = (node->right_ == nullptr) ? -1 : node->right_->height_;
            node->height_ = 1 + std::max(left_height, right_height);
            node->balance_factor_ = right_height - left_height;
        }

        s21::AVLNode<value_type> *balance(s21::AVLNode<value_type> *node) {
            if (node->balance_factor_ == -2) {
                if (node->left_->balance_factor_ <= 0) {
                    return left_small_rotation(node);
                } else {
                    return left_big_rotation(node);
                }
            } else if (node->balance_factor_ == 2) {
                if (node->right_->balance_factor_ >= 0) {
                    return right_small_rotation(node); 
                } else {
                    return right_big_rotation(node);
                }
            }

            return node;
        }

        s21::AVLNode<value_type> *left_small_rotation(s21::AVLNode<value_type> *node) S21_NOEXCEPT {
            return right_rotation(node);
        }

        s21::AVLNode<value_type> *left_big_rotation(s21::AVLNode<value_type> *node) S21_NOEXCEPT {
            node->left_ = left_rotation(node->left_);
            return left_small_rotation(node);
        }

        s21::AVLNode<value_type> *right_small_rotation(s21::AVLNode<value_type> *node) S21_NOEXCEPT {
            return left_rotation(node);
        }

        s21::AVLNode<value_type> *right_big_rotation(s21::AVLNode<value_type> *node) S21_NOEXCEPT {
            node->right_ = right_rotation(node->right_);
            return right_small_rotation(node);
        }

        s21::AVLNode<value_type> *left_rotation(s21::AVLNode<value_type> *node) S21_NOEXCEPT {
            s21::AVLNode<value_type> *transplant_node = node->right_;
            node->right_ = transplant_node->left_;
            transplant_node->left_ = node;

            //reset_parents(node, transplant_node);
            node_update(node);
            node_update(transplant_node);
            return transplant_node;
        }

        s21::AVLNode<value_type> *right_rotation(s21::AVLNode<value_type> *node) S21_NOEXCEPT {
            s21::AVLNode<value_type> *transplant_node = node->left_;
            node->left_ = transplant_node->right_;
            transplant_node->right_ = node;

            //reset_parents(node, transplant_node);
            node_update(node);
            node_update(transplant_node);
            return transplant_node;
        }


    private:
        s21::AVLNode<value_type> *root_;
        size_type size_;
        node_alloc n_alloc;
        Cmp comp_;
    };
}

#endif  // AVL_TREE_HPP_