#ifndef QUEUE_H
#define QUEUE_H

#include <mutex>
#include <deque>
#include <condition_variable>

template <class T>
class MessageQueue
{
public:
    T receive();
    void send(T &&msg);
    void finish();
   
private:
    bool _finished = false;
    std::mutex _mutex;
    std::condition_variable _cond;
    std::deque<T> _messages;
};

#include "queue.tpp"

#endif

