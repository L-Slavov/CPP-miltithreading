//
// Created by lyubomir on 8/19/17.
//

#ifndef CPP_MULTITHREADING_CHANNEL_H
#define CPP_MULTITHREADING_CHANNEL_H

#include <queue>
#include <mutex>
#include <condition_variable>


template <class item>
class Channel {
private:
    std::queue<item> queue;
    std::mutex mu;
    std::condition_variable cv;
public:
    void put(const item &i){
        std::unique_lock<std::mutex> lock (mu);
        queue.push(i);
        cv.notify_one();
    }
    item get(){
        std::unique_lock<std::mutex> lock (mu);
        cv.wait(lock, [&](){ return !queue.empty();});
        item result = queue.front();
        queue.pop();
        return result;
    }
    bool empty(){
        return queue.empty();
    }

};


#endif //CPP_MULTITHREADING_CHANNEL_H
