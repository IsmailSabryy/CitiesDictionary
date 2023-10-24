#pragma once
#include <iostream>
using namespace std;
template <class Type>
class Queuet {
public:
    Queuet(int nelements = 128)
        : MaxSize(nelements), front(1), rear(0), count(0) {
        queue = new Type[MaxSize];
    }

    Queuet(const Queuet<Type>& original)
        : MaxSize(original.MaxSize), front(original.front), rear(original.rear), count(original.count) {
        queue = new Type[MaxSize];
        for (int i = 0; i < MaxSize; i++) queue[i] = original.queue[i];
    }

    ~Queuet() {
        delete[] queue;
    }

    void enqueue(Type v) {
        if (queueIsFull()) cout << "Queue is Full" << endl;
        else {
            rear = (rear + 1) % MaxSize;
            queue[rear] = v;
            count++;
        }
    }

    void dequeue(Type& v) {
        if (queueIsEmpty()) cout << "Queue is Empty" << endl;
        else {
            v = queue[front];
            front = (front + 1) % MaxSize;
            count--;
        }
    }

    void queueFront(Type& v) const {
        if (queueIsEmpty()) cout << "Queue is Empty" << endl;
        else v = queue[front];
    }

    bool queueIsEmpty() const {
        return (count == 0);
    }

    bool queueIsFull() const {
        return (count == MaxSize);
    }

    int queueLength() const {
        return count;
    }

private:
    Type* queue;
    int front, rear, count, MaxSize;
};


