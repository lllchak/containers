#ifndef SRC_LIST_LIST_ITERATOR_H_
#define SRC_LIST_LIST_ITERATOR_H_

#include "list_node.hpp"

namespace s21 {

template <class ListNode, class T>
class ListIterator {
    public:
        using value_type = T;

    public:
        ListIterator() : ptr_(nullptr) {}
        ListIterator(ListNode* src) : ptr_(src) {}
        ~ListIterator() { this->ptr_ = nullptr; }

    public:
        ListIterator& operator++() {
            if (ptr_) ptr_ = ptr_->next_;
            return *this;
        }

        ListIterator operator++(int) {
            ListIterator it(*this);
            ++*this;
            return it;
        }

        value_type& operator*() { return ptr_->data_; }

        bool operator==(const ListNode* src) const { return (src == ptr_); }
        bool operator!=(const ListNode* src) const { return (src != ptr_); }

    private:
        ListNode* ptr_;
};

}

#endif  // SRC_LIST_LIST_ITERATOR_H_