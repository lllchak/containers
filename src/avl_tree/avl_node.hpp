#ifndef AVL_NODE_HPP_
#define AVL_NODE_HPP_

#define S21_NOEXCEPT throw()

namespace S21 {

    template<class T>
    class AVLNode {
    public:
        using value_type = T;
        using difference_type = int;

    public:
        difference_type height_;
        value_type      data_;
        AVLNode         *left_;
        AVLNode         *right_;
        AVLNode         *parent_;
        difference_type balance_factor_;
    
    public:
        AVLNode() : data_(nullptr), left_(nullptr), right_(nullptr), parent_(nullptr), height_(0) {}
        explicit AVLNode(value_type src) : data_(src), left_(nullptr), right_(nullptr), parent_(nullptr), height_(0) {}
        AVLNode(const AVLNode& src) : data_(src.data_), left_(src.left_), right_(src.right_), parent_(nullptr), height_(src.height_) {}
        virtual ~AVLNode(){};

        AVLNode& operator=(const AVLNode& src) S21_NOEXCEPT{
            height_ = src.height_;
            data_ = src.data_;
            left_ = src.left_; parent_ = src.parent_;
            right_ = src.right_;
            balance_factor_ = src.balance_factor_;
        }

        friend bool operator==(const AVLNode& lhs, const AVLNode& rhs) S21_NOEXCEPT {
            return (lhs.data_ == rhs.data_);
        }

        friend bool operator!=(const AVLNode& lhs, const AVLNode& rhs) S21_NOEXCEPT {
            return (lhs.data_ != rhs.data_);
        }
    };
}

#endif