#pragma once

typedef Plane Queue_entry;

class Queue
{
    public:
        Queue();
        bool empty() const;
        Error_code serve();
        Error_code append(const Queue_entry &item);
        Error_code retrieve(Queue_entry &item) const;

    protected:
        int count;
        int front;
        int rear;
        static const int maxqueue = 1024;
        Queue_entry entry[maxqueue];
};
