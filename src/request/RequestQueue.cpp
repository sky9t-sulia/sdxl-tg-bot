#include <request/RequestQueue.h>

RequestQueue::RequestQueue(int maxSize) : maxSize(maxSize), currentSize(0)
{
    items = new RequestQueueItem[maxSize];
}

RequestQueue::~RequestQueue()
{
    delete[] items;
}

bool RequestQueue::add(String statusUrl, String chatId)
{
    if (isFull())
    {
        return false;
    }

    items[currentSize].statusUrl = statusUrl;
    items[currentSize].chatId = chatId;
    currentSize++;

    return true;
}

void RequestQueue::remove(int index)
{
    if (index < 0 || index >= currentSize)
    {
        return;
    }

    for (int i = index; i < currentSize - 1; i++)
    {
        items[i] = items[i + 1];
    }

    currentSize--;
}

bool RequestQueue::isFull() const
{
    return currentSize == maxSize;
}

bool RequestQueue::isEmpty() const
{
    return currentSize == 0;
}

RequestQueueItem &RequestQueue::getItem(int index)
{
    return items[index];
}

int RequestQueue::size() const
{
    return currentSize;
}