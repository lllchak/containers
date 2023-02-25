#ifndef SRC_LIST_LIST_H_
#define SRC_LIST_LIST_H_

#include <stdexcept>
#include <limits>
#include <iostream>


namespace s21 {

template <typename T>
class list {

public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;

private:
    class ListNode {
    public:
        value_type data_;
        ListNode* prev_ = nullptr;
        ListNode* next_ = nullptr;

    public:
        ListNode() = default;
        ListNode(const value_type& value) : data_(value), prev_(nullptr), next_(nullptr) {}
        ListNode(const ListNode& src) : data_(src.data_), prev_(src.prev_), next_(src.next_) {}
        ~ListNode() = default;

        ListNode& operator=(const ListNode& src) noexcept {
            data_ = src.data_;
            prev_ = src.prev_;
            next_ = src.next_;

            return *this;
        }
    };

private:
    ListNode* head_ = nullptr;
    ListNode* tail_ = nullptr;
    size_type size_ = 0;


public:
    list() = default;
    ~list() { clear(); }

    list<value_type>& operator=(list<value_type> src) {
        size_ = src.size_;
        std::swap(head_, src.head_);
        std::swap(tail_, src.tail_);

        return *this;
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& stream, const list<U>& head);

public:

    void push_front(const_reference data) {
        ListNode* new_node = new ListNode(data);
        if (!head_) head_ = tail_ = new_node;
        else {
            new_node->next_ = head_;
            head_->prev_ = new_node;
            head_ = new_node;
        }
        
        size_++;
    }

    void push_back(const_reference data) {
        ListNode* new_node = new ListNode(data);
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
        ListNode* curr = head_;
        while (curr) {
            ListNode* next = curr->next_;
            delete curr;
            curr = next;
        }
    }

};

template <typename T>
std::ostream& operator<<(std::ostream& stream, const list<T>& head) {
    if (head.empty()) {
        stream << "List is empty";
        return stream;
    }

    ListNode* curr = head.head_;
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

}  // namespace s21


#endif  // SRC_LIST_LIST_H_
