#ifndef SRC_LIST_LIST_H_
#define SRC_LIST_LIST_H_

#include <stdexcept>
#include <limits>
#include <iostream>

#include "list_node.hpp"

namespace s21 {

template <class T>
class list {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using size_type = std::size_t;
    
    public:
        list() : head_(nullptr), size_(0) {}
        // list(const size size_type);
        // list(const list& other);
        // list(list&& other);
        // ~list();

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
};

}  // namespace s21

#endif  // SRC_LIST_LIST_H_
