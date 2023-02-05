#ifndef SRC_LIST_LIST_H_
#define SRC_LIST_LIST_H_

#include <stdexcept>
#include <limits>
#include <iostream>

#include "list_node.hpp"
#include "list_iterator.hpp"

namespace s21 {
    
template <class T>
class list {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using size_type = std::size_t;

    public:
        using iterator = ListIterator<ListNode<value_type>, value_type>;
        using const_iterator = ListIterator<const ListNode<value_type>, const value_type>;
    
    public:
        list() : head_(nullptr), size_(0) {}
        // list(const size size_type);
        // list(const list& other);
        // list(list&& other);
        ~list() { this->clear(); }

        list<value_type>& operator=(list<value_type>& src) {
            size_ = src.size_;
            std::copy(src.begin(), src.end(), (*this).begin());
        }

        friend std::ostream& operator<<(std::ostream& stream, const list<value_type>& head) {
            if (head.empty()) {
                stream << "List is empty";
                return stream;
            }
            
            ListNode<value_type>* tmp = head.head_;
            stream << "NULL <-> " << tmp->data_ << " <-> ";
            tmp = tmp->next_;

            while (tmp && tmp->next_) {
                if (tmp->prev_->next_->data_ == tmp->next_->prev_->data_) {
                    stream << tmp->data_ << " <-> ";
                } else {
                    stream << "Invalid list";
                    return stream;
                }
                tmp = tmp->next_;
            }

            if (tmp) stream << tmp->data_ << " <-> ";
            stream << "NULL" << std::endl;

            return stream;
        }

    public:
        s21::ListNode<value_type>* begin() { return head_; }
        s21::ListNode<value_type>* begin() const { return head_; }
        s21::ListNode<value_type>* end() { return nullptr; }
        s21::ListNode<value_type>* end() const { return nullptr; }

        void push_front(const_reference data) {
            s21::ListNode<value_type>* new_node = new s21::ListNode(data);
            if (!head_) head_ = tail_ = new_node;
            else {
                new_node->next_ = head_;
                head_->prev_ = new_node;
                head_ = new_node;
            }
            
            size_++;
        }

        void push_back(const_reference data) {
            s21::ListNode<value_type>* new_node = new s21::ListNode(data);
            if (!head_) head_ = tail_ = new_node;
            else {
                tail_->next_ = new_node;
                new_node->prev_ = tail_;
                tail_ = new_node;
            }

            size_++;
        }

        bool empty() const noexcept { return (size_ == 0); }
        size_type size() const noexcept { return size_; }
        // size_type max_size() const noexcept { 
        //     return std::numeric_limits<size_type>::max() / sizeof(s21::ListNode); 
        // }

    private:
        s21::ListNode<value_type>* head_;
        s21::ListNode<value_type>* tail_;
        size_type size_;

    private:
        void clear() {
            ListNode<value_type>* tmp = head_;
            while (tmp) {
                ListNode<value_type>* next = tmp->next_;
                delete tmp;
                tmp = next;
            }

            head_ = nullptr;
        }

};

}  // namespace s21

#endif  // SRC_LIST_LIST_H_
