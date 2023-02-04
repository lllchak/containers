#ifndef SRC_LIST_LIST_H_
#define SRC_LIST_LIST_H_

#include <stdexcept>

namespace s21 {

template <class value_type>
class list {
    using const_referece = const value_type&;
    using size_type = std::size_t;

    public:
        list() {
            this->curr_node_ = new ListNode();
            this->curr_node_->next_ = nullptr;
            this->curr_node_->prev_ = nullptr;
            this->size_ = 0;
        }
        // list(const size size_type);
        // list(const list& other);
        // list(list&& other);
        // ~list();

        bool empty() const noexcept {
            return (
                this->curr_node_->next_ == nullptr &&
                this->curr_node_->prev_ == nullptr
            );
        }
        size_type size() const noexcept { return this->size_; }

    private:
        struct ListNode {
            value_type data_;
            ListNode* prev_;
            ListNode* next_;
            ListNode() : data_(), prev_(nullptr), next_(nullptr) {}
            ListNode(const T& value) : data_(value), prev_(nullptr), next_(nullptr) {}
        };

        size_type size_;
        ListNode* curr_node_;
};

}  // namespace s21

#endif  // SRC_LIST_LIST_H_
