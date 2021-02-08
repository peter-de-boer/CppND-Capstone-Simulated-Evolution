#include <thread>


template <class T>
T MessageQueue<T>::receive()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    // perform queue modification under the lock
    std::unique_lock<std::mutex> uLock(_mutex);
    _cond.wait(uLock, [this] { return !_messages.empty() || _finished; }); // pass unique lock to condition variable
    // remove last vector element from queue
    
    if (!_messages.empty()) {
        
        T msg = std::move(_messages.back());
        
        _messages.pop_back();
   
        return msg; // will not be copied due to return value optimization (RVO) in C++
    } else { // _finished is true, return an empty object
       T msg;
       return msg;
    }
}

template <class T>
void MessageQueue<T>::send(T &&msg)
{

    // simulate some work
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    // perform vector modification under the lock
    std::lock_guard<std::mutex> uLock(_mutex);

    // add vector to queue

    _messages.push_back(std::move(msg));

    _cond.notify_one(); // notify client after pushing new Vehicle into vector

}

template <class T>
void MessageQueue<T>::finish()
{
    std::lock_guard<std::mutex> uLock(_mutex);
    _finished = true;
    _cond.notify_one();
}