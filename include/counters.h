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

    Counters(const std::vector<K> &keys) {
        for (K k : keys)
            counters[k] = 0;
    }

    void increment(K k, T value);
    void batch_increment(std::map<K, T> &values);
    const std::map<K, T> &get_counters();

};

#endif //BRANDES_COUNTERS_H
