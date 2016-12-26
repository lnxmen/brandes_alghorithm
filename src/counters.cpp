#include <mutex>
#include "graph.h"
#include "counters.h"

template<typename K, typename T, bool synchronized>
void Counters<K, T, true>::increment(K v, T value) {
    std::lock_guard <std::mutex> lock(m);
    counters[v] += value;
}

template<typename K, typename T, bool synchronized>
void Counters<K, T, false>::increment(K v, T value) {
    counters[v] += value;
}

template<typename K, typename T, bool synchronized>
void Counters<K, T, true>::batch_increment(std::map<K, T> &values) {
    std::lock_guard <std::mutex> lock(m);
    for (auto &kv : values)
        counters[kv.first] += kv.second;
}

template<typename K, typename T, bool synchronized>
void Counters<K, T, false>::batch_increment(std::map<K, T> &values) {
    for (auto &kv : values)
        counters[kv.first] += kv.second;
}

template<typename K, typename T, bool synchronized>
const std::map<K, T> &Counters<K, T, true>::get_counters() {
    if (synchronized)
        std::lock_guard<std::mutex> lock(m);
    return counters;
}

template<typename K, typename T, bool synchronized>
const std::map<K, T> &Counters<K, T, false>::get_counters() {
    return counters;
}