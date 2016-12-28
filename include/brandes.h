#ifndef BRANDES_BRANDES_H
#define BRANDES_BRANDES_H

#include <map>
#include <mutex>
#include "graph.h"
#include "manager.h"
#include "counters.h"

template<typename T>
class Brandes {

    using counterType = double;

    Graph<T> &graph_;
    Manager<T> manager_;
    Counters<T, counterType, true> counters_;

public:

    Brandes(Graph<T> &graph) : graph_(graph) {
        manager_.add_jobs(graph_);
        counters_.initialize_values(graph_);
    }

    std::map<T, counterType> &get_result() { return counters_.get_counters(); }

    void run(int threads);

private:

    void run_worker();

    void compute(T s, Counters<T, counterType, false> *counters);

};

template
class Brandes<int>;

#endif //BRANDES_BRANDES_H
