#ifndef SRC_LIST_LIST_H_
#define SRC_LIST_LIST_H_

#include <stdexcept>

namespace s21 {

using size = std::size_t;

template <class T>
class list {
    public:
        list();
        list(const size lsize);
        list(const list& other);
        list(list&& other);
        ~list();

    private:
        struct ListNode {
            T data_;
            ListNode* next_;
            ListNode* prev_;
            ListNode() : data_(), prev_(nullptr), next_(nullptr) {}
        }

        size size_;
        ListNode* curr_node_;
}

}  // namespace s21

#endif  // SRC_LIST_LIST_H_
