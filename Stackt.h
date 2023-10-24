#pragma once
#include <iostream>
using namespace std;
template <class Type>
class Stackt {
public:
    Stackt(int nelements = 128)
        : MaxSize(nelements), stack(new Type[MaxSize]), top(-1) {
    }

    Stackt(const Stackt<Type>& original)
        : MaxSize(original.MaxSize), top(original.top) {
        stack = new Type[MaxSize];
        for (int i = 0; i <= top; i++) stack[i] = original.stack[i];
    }

    ~Stackt() {
        delete[] stack;
    }

    void push(Type v) {
        if (stackIsFull()) cout << "Stack Overflow" << endl;
        else stack[++top] = v;
    }

    void pop(Type& v) {
        if (stackIsEmpty()) cout << "Stack Underflow" << endl;
        else v = stack[top--];
    }

    void stackTop(Type& v) const {
        if (stackIsEmpty()) cout << "Stack Underflow";
        else v = stack[top];
    }

    bool stackIsEmpty() const {
        return (top < 0);
    }

    bool stackIsFull() const {
        return (top >= (MaxSize - 1));
    }

private:
    Type* stack;
    int top, MaxSize;
};



