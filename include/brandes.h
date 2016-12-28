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
    Manager<T> manager_;
    Counters<T, C, true> counters_;

public:

    Brandes(Graph<T> &graph) : graph_(graph) {
        manager_.add_jobs(graph_);
        counters_.initialize_values(graph_);
    }

    std::map<T, C> get_result();

    void run(int threads);

private:

    void run_worker();

    void compute(T s, Counters<T, C, false> *counters);

};

template
class Brandes<int, double>;

#endif //BRANDES_BRANDES_H
