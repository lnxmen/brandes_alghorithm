#ifndef BRANDES_COUNTERS_H
#define BRANDES_COUNTERS_H

#include <unordered_map>
#include <mutex>
#include "graph.h"

template<typename K, typename T, bool synchronized>
class Counters {

    std::vector<T> counters;
    std::mutex m;

public:

    void initialize_values(Graph<K> &graph);

    void increment(IDType k, T value);

    void batch_increment(std::vector<T> &values);

    std::vector<T> &get_counters();

};

template // with synchronization
class Counters<int, double, true>;

template // without synchronization
class Counters<int, double, false>;

#endif //BRANDES_COUNTERS_H
