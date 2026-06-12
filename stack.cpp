#include "stack.h"

Stack::Stack() : top_(nullptr), size_(0) {}

Stack::~Stack() {
    while (top_ != nullptr) {
        Node* tmp = top_;
        top_ = top_->next;
        delete tmp;
    }
}

void Stack::push(int val) {
    Node* node = new Node(val);
    node->next = top_;
    top_  = node;
    ++size_;
}

void Stack::pop() {
    if (top_ == nullptr)
        throw std::underflow_error("pop on empty stack");
    Node* tmp = top_;
    top_ = top_->next;
    delete tmp;
    --size_;
}

int Stack::peek() const {
    if (top_ == nullptr)
        throw std::underflow_error("peek on empty stack");
    return top_->value;
}

bool Stack::empty() const {
    return top_ == nullptr;
}

int Stack::size() const {
    return size_;
}
