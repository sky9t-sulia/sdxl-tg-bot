#ifndef REQUEST_QUEUE_H
#define REQUEST_QUEUE_H

#include <Arduino.h>

struct RequestQueueItem
{
    String chatId;
    String statusUrl;
};

class RequestQueue
{
public:
    RequestQueue(int maxSize);
    ~RequestQueue();

    RequestQueueItem& getItem(int index) {
        if(index < 0 || index >= currentSize) {
            // Handle error: index out of range
        }
        return items[index];
    }

    bool add(String statusUrl, String chatId);
    void remove(int index);
    bool isFull() const;
    bool isEmpty() const;
    int size() const;

private:
    RequestQueueItem *items;
    int maxSize;
    int currentSize;
};

#endif // QUEUE_H