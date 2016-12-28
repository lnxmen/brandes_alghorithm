#include <mutex>
#include <graph.h>
#include "manager.h"

template<typename T>
void Manager<T>::add_jobs(Graph<T> &graph) {
    std::lock_guard<std::mutex> lock(mutex_);
    for (T k : *graph.get_vertexes_ids())
        jobs_.push(k);
}

template<typename T>
T *Manager<T>::take_job() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (jobs_.empty())
        return nullptr;
    T &job = jobs_.front();
    jobs_.pop();
    return &job;
}