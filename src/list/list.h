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
        list() {}
        ~list() { clear(); }

        list<value_type>& operator=(list<value_type> src) {
            size_ = src.size_;
            std::swap(head_, src.head_);
            std::swap(tail_, src.tail_);

            return *this;
        }

        friend std::ostream& operator<<(std::ostream& stream, const list<value_type>& head) {
            if (head.empty()) {
                stream << "List is empty";
                return stream;
            }
            
            ListNode<value_type>* curr = head.head_;
            stream << "NULL <-> " << curr->data_ << " <-> ";
            curr = curr->next_;

            while (curr && curr->next_) {
                if (curr->prev_->next_->data_ == curr->next_->prev_->data_) {
                    stream << curr->data_ << " <-> ";
                } else {
                    stream << "Invalid list";
                    return stream;
                }
                curr = curr->next_;
            }

            if (curr) stream << curr->data_ << " <-> ";
            stream << "NULL" << std::endl;

            return stream;
        }

    public:
        ListNode<value_type>* begin() { return head_; }
        ListNode<value_type>* begin() const { return head_; }
        ListNode<value_type>* end() { return nullptr; }
        ListNode<value_type>* end() const { return nullptr; }

        void push_front(const_reference data) {
            ListNode<value_type>* new_node = new ListNode(data);
            if (!head_) head_ = tail_ = new_node;
            else {
                new_node->next_ = head_;
                head_->prev_ = new_node;
                head_ = new_node;
            }
            
            size_++;
        }

        void push_back(const_reference data) {
            ListNode<value_type>* new_node = new ListNode(data);
            if (!head_) head_ = tail_ = new_node;
            else {
                tail_->next_ = new_node;
                new_node->prev_ = tail_;
                tail_ = new_node;
            }

            size_++;
        }

        bool empty() const noexcept { return (!size_); }
        size_type size() const noexcept { return size_; }

    private:
        ListNode<value_type>* head_ = nullptr;
        ListNode<value_type>* tail_ = nullptr;
        size_type size_ = 0;

    private:
        void clear() {
            ListNode<value_type>* curr = head_;
            while (curr) {
                ListNode<value_type>* next = curr->next_;
                delete curr;
                curr = next;
            }
        }

};

}  // namespace s21

#endif  // SRC_LIST_LIST_H_
