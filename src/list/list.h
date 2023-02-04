#ifndef SRC_LIST_LIST_H_
#define SRC_LIST_LIST_H_

#include <stdexcept>
#include <limits>
#include <iostream>

namespace s21 {

template <class value_type>
class list {
    using reference = value_type&;
    using const_reference = const value_type&;
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

        friend std::ostream& operator<<(std::ostream& stream, const list<value_type>& head);

        void push_back(const_reference data) {
            if (this->size_ >= this->max_size() - 1) {
                throw std::out_of_range("Container if full");
            }

            ListNode* new_node = new ListNode(data);
            if (!this->curr_node_) {
                this->curr_node_ = new_node;
                this->size_ = 1;
            }
            else {
                ListNode* tmp = this->curr_node_;
                tmp->next_ = new_node;
                new_node->next_ = nullptr;
                new_node->prev_ = tmp;
                this->size_++;
            }
        }

        bool empty() const noexcept {
            return (
                this->curr_node_->next_ == nullptr &&
                this->curr_node_->prev_ == nullptr
            );
        }
        size_type size() const noexcept { return this->size_; }
        size_type max_size() const noexcept { 
            return std::numeric_limits<size_type>::max() / sizeof(ListNode); 
        }

    private:
        struct ListNode {
            value_type data_;
            ListNode* prev_;
            ListNode* next_;
            ListNode() : data_(), prev_(nullptr), next_(nullptr) {}
            ListNode(const_reference value) : data_(value), prev_(nullptr), next_(nullptr) {}
        };

        size_type size_;
        ListNode* curr_node_;
};

}  // namespace s21

#endif  // SRC_LIST_LIST_H_
