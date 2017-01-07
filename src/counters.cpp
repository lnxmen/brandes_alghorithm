#include <mutex>
#include "graph.h"
#include "counters.h"

template<typename K, typename T, bool synchronized>
void Counters<K, T, synchronized>::initialize_values(Graph<K> &graph) {
    if (synchronized)
        std::lock_guard<std::mutex> lock(m);

    std::vector<Vertex> *vertexes = graph.get_vertexes();

    while (counters.size() < vertexes->size())
        counters.emplace_back(0);

    for (Vertex &v : *vertexes)
        counters[v.get_id()] = 0;
};


template<typename K, typename T, bool synchronized>
void Counters<K, T, synchronized>::increment(IDType v, T value) {
    if (synchronized)
        std::lock_guard<std::mutex> lock(m);
    counters[v] += value;
}

template<typename K, typename T, bool synchronized>
void Counters<K, T, synchronized>::batch_increment(std::vector<T> &values) {
    if (synchronized)
        std::lock_guard<std::mutex> lock(m);

    for (auto i = 0; i < values.size(); i++)
        counters[i] = counters[i] + values[i];
}

template<typename K, typename T, bool synchronized>
std::vector<T> &Counters<K, T, synchronized>::get_counters() {
    if (synchronized)
        std::lock_guard<std::mutex> lock(m);
    return counters;
}