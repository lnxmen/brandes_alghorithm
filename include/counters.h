#ifndef BRANDES_COUNTERS_H
#define BRANDES_COUNTERS_H

#include <map>
#include <mutex>
#include "graph.h"

template<typename K, typename T, bool synchronized>
class Counters {
    std::map<K, T> counters;
    std::mutex m;

public:

    void initialize_values(Graph<K> &graph);

    void increment(K k, T value);

    void batch_increment(std::map<K, T> &values);

    std::map<K, T> &get_counters();
};

template // with synchronization
class Counters<int, double, true>;

template // without synchronization
class Counters<int, double, false>;

#endif //BRANDES_COUNTERS_H
