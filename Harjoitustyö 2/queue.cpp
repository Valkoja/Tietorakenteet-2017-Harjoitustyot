#include "main.h"

Queue::Queue()
{
    count = 0;
    rear = maxqueue - 1;
    front = 0;
}

bool Queue::empty() const
{
    return count == 0;
}

Error_code Queue::append(const Queue_entry &item)
{
    if (count >= maxqueue)
    {
        return Error_code::overflow;
    }

    count++;
    rear = ((rear + 1) == maxqueue) ? 0 : (rear + 1);
    entry[rear] = item;

    return Error_code::success;
}

Error_code Queue::serve()
{
    if (count <= 0)
    {
        return Error_code::underflow;
    }

    count--;
    front = ((front + 1) == maxqueue) ? 0 : (front + 1);

    return Error_code::success;
}

Error_code Queue::retrieve(Queue_entry &item) const
{
    if (count <= 0)
    {
        return Error_code::underflow;
    }

    item = entry[front];

    return Error_code::success;
}
