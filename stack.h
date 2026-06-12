#pragma once
#include <stdexcept>

/*
 * Узел односвязного списка — хранит значение (вид топлива)
 * и указатель на следующий элемент.
 */
struct Node {
    int   value;
    Node* next;

    explicit Node(int v) : value(v), next(nullptr) {}
};

/*
 * Стек на основе односвязного списка (LIFO).
 * Запрет копирования предотвращает двойное освобождение памяти.
 */
class Stack {
private:
    Node* top_;
    int   size_;

public:
    Stack();
    ~Stack();

    Stack(const Stack&)            = delete;
    Stack& operator=(const Stack&) = delete;

    void push(int val);
    void pop();
    int  peek() const;
    bool empty() const;
    int  size()  const;
};
