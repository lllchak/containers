#ifndef SRC_LIST_LIST_NODE_H_
#define SRC_LIST_LIST_NODE_H_

namespace s21 {

template <class T>
class ListNode {
    public:
        using value_type = T;
        using const_reference = const ListNode&;

    public:
        value_type data_;
        ListNode* prev_;
        ListNode* next_;

    public:
        ListNode() : data_(), prev_(nullptr), next_(nullptr) {}
        explicit ListNode(value_type value) : data_(value), prev_(nullptr), next_(nullptr) {}
        ListNode(const_reference src) : data_(src.data_), prev_(src.prev_), next_(src.next_) {}
        virtual ~ListNode() {}

        ListNode& operator=(const_reference src) noexcept {
            data_ = src.data_;
            prev_ = src.prev_;
            next_ = src.next_;
        }
};

}

#endif  // SRC_LIST_LIST_NODE_H_