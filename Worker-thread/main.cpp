#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Channel.h"



void worker_thread(Channel<std::string>* data)
{
    while(true){
        auto Channeldata = data->get();
        if(Channeldata == "END"){
            break;
        }
        std::cout << "Worker says: " << Channeldata << std::endl;
    }
    std::cout << "Exiting loop" << std::endl;
}

int main()
{
    Channel<std::string>* myChan = new Channel<std::string>;

    myChan->put("Hello");
    myChan->put("World");

    std::thread worker(worker_thread,myChan);

    while (true){
        std::string input;
        std::cin >> input;
        myChan->put(input);
        if(input == "END"){
            break;
        }
    }

    worker.join();
}