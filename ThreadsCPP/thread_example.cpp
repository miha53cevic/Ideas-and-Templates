//
// Author: Mihael Petricevic
// Contact: miha53cevic@gmail.com
// Date: 21.5.2019.
//  
// Sources: 
// https://www.geeksforgeeks.org/multithreading-in-cpp/
// https://en.cppreference.com/w/cpp/thread/mutex
// https://en.cppreference.com/w/cpp/thread/lock_guard
//
// Compile command: g++ -std=c++17 -pthread -o threadExample thread_example.cpp 
//

#include <iostream>
#include <thread>   // Must add -pthread when compiling
#include <mutex>

int main(int argc, char* argv[])
{
    // Defenition of a mutex

    // The mutex class is a synchronization primitive
    // that can be used to protect shared data from 
    // being simultaneously accessed by multiple threads.

    // Protects i or any variable from being used by the other thread
    std::mutex i_mutex;

    std::thread helper1([&](){

        // First we lock the mutex with lock_guard and it only gets released
        // when lock_guard goes out of scope
        std::lock_guard<std::mutex> lock(i_mutex);

        for (int i = 0; i < 5; i++)
        {
            std::cout << "helper1: counting... " << i << "\n";
        }
    });

    std::thread helper2([&](){

        // We do the same thing for the second thread so when it gets called it
        // gets called it locks the mutex and so the other thread can't use resources
        std::lock_guard<std::mutex> lock(i_mutex);

        for (int i = 5; i < 10; i++)
        {
            std::cout << "helper2: counting... " << i << "\n";
        }
    });

    // Wait till helper1 finishes - helper2 is still running as well at the same time
    helper1.join();

    // Wait for helper2 to finish
    helper2.join();

    /*
        Output:
                helper1: counting... 1
                ...
                helper1: counting... 4
                helper2: counting... 5
                ...
                helper2: counting... 9
    */

    return 0;
}