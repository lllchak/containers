#ifndef SRC_LIST_LIST_H_
#define SRC_LIST_LIST_H_

#include <stdexcept>
#include <limits>
#include <iostream>


namespace s21 {
    
template <typename T>
class ListNode {
public:
    using value_type = T;
    using const_refernce = const T&;

public:
    value_type data_;
    ListNode* prev_ = nullptr;
    ListNode* next_ = nullptr;

public:
    bool operator==(const ListNode& other) { return data_ == other.data_; }
    bool operator!=(const ListNode& other) { return !(*this == other); }

    ListNode& operator=(const ListNode& src) noexcept {
        data_ = src.data_;
        prev_ = src.prev_;
        next_ = src.next_;

        return *this;
    }

    ListNode() = default;
    ListNode(const_refernce value)      : data_(value), prev_(nullptr), next_(nullptr) {}
    ListNode(const ListNode& src) : data_(src.data_), prev_(src.prev_), next_(src.next_) {}
    ~ListNode() = default;

};

template <typename T>
class ListIterator {
public:
    using value_type = T;

public:
    ListIterator() {}
    ListIterator(ListNode<value_type>* src) : node_(src) {}

public:
    bool operator==(const ListIterator& other) { return node_ == other.node_; }
    bool operator!=(const ListIterator& other) { return !(node_ == other.node_); }
    T& operator*() const { return node_->data_; }
    T* operator->() const { return &node_->data_; }

    ListIterator& operator++() { 
        node_ = node_->next_; 
        return *this; 
    }

    ListIterator operator++(int) { 
        ListIterator res(*this);
        ++(*this); 
        return res;
    }

    ListIterator& operator--() { 
        node_ = node_->prev_;
        return *this;
    }

    ListIterator operator--(int) { 
        ListIterator res(*this); 
        --(*this); 
        return res; 
    }

private:
    ListNode<value_type>* node_ = nullptr;
};

template <typename T>
class list {
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using iterator = ListIterator<T>;

public:
    list() {};
    ~list() { clear(); }

    iterator begin() { return head_; }
    iterator end() { return nullptr; }

    ListNode<value_type>* get_head(void) const { return head_; }
    ListNode<value_type>* get_tail(void) const { return tail_; }

    list<value_type>& operator=(list<value_type>& src) {
        std::swap(size_, src.size_);
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
