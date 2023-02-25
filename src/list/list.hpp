#ifndef SRC_LIST_LIST_H_
#define SRC_LIST_LIST_H_

#include <stdexcept>
#include <limits>
#include <iostream>


namespace s21 {
    
template <typename T>
class ListNode {
public:
    T data_;
    ListNode* prev_ = nullptr;
    ListNode* next_ = nullptr;

public:
    ListNode() = default;
    ListNode(const T& value) : data_(value), prev_(nullptr), next_(nullptr) {}
    ListNode(const ListNode& src) : data_(src.data_), prev_(src.prev_), next_(src.next_) {}
    ~ListNode() = default;

    ListNode& operator=(const ListNode& src) noexcept {
        data_ = src.data_;
        prev_ = src.prev_;
        next_ = src.next_;

        return *this;
    }
};

template <typename T>
class list {

public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;

private:
    ListNode<value_type>* head_ = nullptr;
    ListNode<value_type>* tail_ = nullptr;
    size_type size_ = 0;

public:
    list() = default;
    ~list() { clear(); }

    ListNode<value_type>* get_head(void) const { return head_; }
    ListNode<value_type>* get_tail(void) const { return tail_; }

    list<value_type>& operator=(list<value_type> src) {
        size_ = src.size_;
        std::swap(head_, src.head_);
        std::swap(tail_, src.tail_);

        return *this;
    }

public:
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
