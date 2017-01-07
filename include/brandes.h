#ifndef BRANDES_BRANDES_H
#define BRANDES_BRANDES_H

#include <map>
#include <mutex>
#include "graph.h"
#include "manager.h"
#include "counters.h"

template<typename T, typename C>
class Brandes {

    Graph<T> &graph_;
    Manager<IDType> manager_; // Manager gives workers vertices to compute
    Counters<T, C, true> counters_; // Synchronized counters for each vertex

public:

    Brandes(Graph<T> &graph) : graph_(graph) {
        manager_.add_jobs(graph_);
        counters_.initialize_values(graph_);
    }

    std::map<T, C> get_result();

    void run(int threads);

private:

    void run_worker();

    void compute(IDType s, Counters<T, C, false> *counters);
    
};

template
class Brandes<int, double>;

#endif //BRANDES_BRANDES_H
