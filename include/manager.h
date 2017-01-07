#ifndef BRANDES_MANAGER_H
#define BRANDES_MANAGER_H

#include <queue>
#include <mutex>
#include "graph.h"

template<typename T>
class Manager {
    std::queue<T> jobs_;
    std::mutex mutex_;

public:

    void add_jobs(Graph<T> &graph);

    T take_job();
};

template
class Manager<int>;

#endif //BRANDES_MANAGER_H
