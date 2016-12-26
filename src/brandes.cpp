#include <iostream>
#include <thread>
#include "graph.h"
#include "brandes.h"

template<typename T>
void Brandes<T>::run(int threads_number) {

//    for (auto &kv : graph_.get_vertexes())
//        vertexes.push_back(kv.first);

    std::vector<std::thread> threads;

    for (size_t i = 0; i < threads_number; i++)
        threads.push_back(std::thread( [this] { run_worker(); }));

    for (auto& thread : threads)
        thread.join();
}

template<typename T>
void Brandes<T>::run_worker() {

    T *id = manager_.take_job();
    T first_id = -1;

    if (id != nullptr)
        first_id = *id;

    while (id != nullptr) {
        std::cout << first_id << " " << *id << std::endl;
        id = manager_.take_job();
    }
}