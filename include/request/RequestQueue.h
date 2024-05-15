#ifndef REQUEST_QUEUE_H
#define REQUEST_QUEUE_H

#include <Arduino.h>

/**
 * Struct to hold the request queue item.
 */
struct RequestQueueItem
{
    String chatId;    ///< The chat ID.
    String statusUrl; ///< The status URL.
};

/**
 * Class to manage a request queue.
 */
class RequestQueue
{
public:
    /**
     * Constructor for the RequestQueue class.
     *
     * @param maxSize The maximum size of the queue.
     */
    RequestQueue(int maxSize);

    /**
     * Destructor for the RequestQueue class.
     */
    ~RequestQueue();

    /**
     * Get the item at the specified index.
     *
     * @param index The index of the item.
     * @return The item at the specified index.
     */
    RequestQueueItem &getItem(int index);

    /**
     * Add a new item to the queue.
     *
     * @param statusUrl The status URL of the new item.
     * @param chatId The chat ID of the new item.
     * @return true if the item was added successfully, false otherwise.
     */
    bool add(String statusUrl, String chatId);

    /**
     * Remove the item at the specified index from the queue.
     *
     * @param index The index of the item to remove.
     */
    void remove(int index);

    /**
     * Check if the queue is full.
     *
     * @return true if the queue is full, false otherwise.
     */
    bool isFull() const;

    /**
     * Check if the queue is empty.
     *
     * @return true if the queue is empty, false otherwise.
     */
    bool isEmpty() const;

    /**
     * Get the current size of the queue.
     *
     * @return The current size of the queue.
     */
    int size() const;

private:
    RequestQueueItem *items;    ///< The items in the queue.
    int maxSize;                ///< The maximum size of the queue.
    int currentSize;            ///< The current size of the queue.
};

#endif // REQUEST_QUEUE_H