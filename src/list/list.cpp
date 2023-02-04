#include "list.h"

namespace s21 {

template <class T>
list<T>::list() {
    this->curr_node_ = new ListNode();
    this->curr_node_->prev_ = nullptr;
    this->curr_node_->next_ = nullptr;
    this->size_ = 0;
}

template <class T>
bool list<T>::empty() const noexcept {
    return (
        this->curr_node_->next_ == nullptr &&
        this->curr_node_->prev_ == nullptr
    );
}

template <class T>
lsize list<T>::size() const noexcept {
    return this->size_;
}

}