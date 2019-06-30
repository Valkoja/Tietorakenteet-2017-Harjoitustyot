#include "main.h"

Extended_queue::Extended_queue() : Queue()
{
    // Parentin rakentaja
}

bool Extended_queue::full() const
{
    if (count == maxqueue)
    {
        return true;
    }

    return false;
}

int Extended_queue::size() const
{
    return count;
}

void Extended_queue::clear()
{
    count = 0;
    rear = maxqueue - 1;
    front = 0;
}

Error_code Extended_queue::serve_and_retrieve(Queue_entry &item)
{
    if (count <= 0)
    {
        return Error_code::underflow;
    }

    retrieve(item);
    serve();

    return Error_code::success;
}
