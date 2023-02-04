#include "list.h"

namespace s21 {

template <class value_type>
std::ostream& operator<<(std::ostream& stream, const list<value_type>& head) {
    while (head->next_) {
        stream << head->data_ << " -> ";
        head = head->next_;
    }

    stream << "NULL" << std::endl;

    return stream;
}

}
