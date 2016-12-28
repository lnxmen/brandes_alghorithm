#include <mutex>
#include "graph.h"
#include "counters.h"


template<typename K, typename T, bool synchronized>
void Counters<K, T, synchronized>::initialize_values(Graph<K> &graph) {
    if (synchronized)
        std::lock_guard<std::mutex> lock(m);

    for (T k : *graph.get_vertexes_ids())
        counters[k] = 0;
};


template<typename K, typename T, bool synchronized>
void Counters<K, T, synchronized>::increment(K v, T value) {
    if (synchronized)
        std::lock_guard<std::mutex> lock(m);
    counters[v] += value;
}

template<typename K, typename T, bool synchronized>
void Counters<K, T, synchronized>::batch_increment(std::map<K, T> &values) {
    if (synchronized)
        std::lock_guard<std::mutex> lock(m);
    for (auto &kv : values)
        counters[kv.first] += kv.second;
}

template<typename K, typename T, bool synchronized>
std::map<K, T> &Counters<K, T, synchronized>::get_counters() {
    if (synchronized)
        std::lock_guard<std::mutex> lock(m);
    return counters;
}