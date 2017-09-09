#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

std::mutex m;
std::condition_variable cv;


void worker_thread(std::queue<std::string>* data)
{
    while(true){
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk,[data]{ return !data->empty();});
        if(data->front() == "END"){
            data->pop();
            break;
        }
        std::cout << "Worker says: " << data->front() << std::endl;
        data->pop();
        lk.unlock();
    }
    std::cout << "Exiting loop" << std::endl;
}

int main()
{

    std::queue<std::string>* data = new std::queue<std::string>;


    data->push("Hello");
    data->push("World!");

    std::thread worker(worker_thread,data);

    while (true){
        std::string input;
        std::cin >> input;
        data->push(input);
        cv.notify_one();
        if(input == "END"){
            break;
        }
    }

    worker.join();
}