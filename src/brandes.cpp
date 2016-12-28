#include <iostream>
#include <thread>
#include <stack>
#include <unordered_map>
#include "graph.h"
#include "brandes.h"

template<typename T, typename C>
void Brandes<T, C>::run(int threads_number) {
    std::vector<std::thread> threads;

    for (size_t i = 0; i < threads_number; i++)
        threads.push_back(std::thread([this] { run_worker(); }));

    for (auto &thread : threads)
        thread.join();
}

template<typename T, typename C>
void Brandes<T, C>::run_worker() {
    T *id = manager_.take_job();
    Counters<T, C, false> counters_t;

    while (id != nullptr) {
        // compute increments for current vertex
        compute(*id, &counters_t);
        // update global counters
        counters_.batch_increment(counters_t.get_counters());
        // clear local counters
        counters_t.initialize_values(graph_);
        // get next job (vertex)
        id = manager_.take_job();
    }
}

template<typename T, typename C>
void Brandes<T, C>::compute(T s, Counters<T, C, false> *counters) {
    std::stack<T> S;
    std::unordered_map<T, std::vector<T>> previous_vertexes;
    std::unordered_map<T, int> shortest_paths_counter;
    std::unordered_map<T, int> distance;
    std::unordered_map<T, double> betweenness;

    for (T t : *graph_.get_vertexes_ids()) {
        shortest_paths_counter[t] = 0;
        distance[t] = -1;
        betweenness[t] = 0;
    }

    shortest_paths_counter[s] = 1;
    distance[s] = 0;

    std::queue<T> Q;
    Q.push(s);

    T v;
    while (!Q.empty()) {
        v = Q.front();
        Q.pop();
        S.push(v);

        for (T w : graph_.get_vertex(v)->get_edges()) {
            if (distance[w] < 0) {
                Q.push(w);
                distance[w] = distance[v] + 1;
            }
            if (distance[w] == distance[v] + 1) {
                shortest_paths_counter[w] += shortest_paths_counter[v];
                previous_vertexes[w].push_back(v);
            }
        }
    }

    while (!S.empty()) {
        v = S.top();
        S.pop();
        for (T p : previous_vertexes[v])
            betweenness[p] += (C(shortest_paths_counter[p]) / shortest_paths_counter[v]) * (1.0 + betweenness[v]);
        if (v != s)
            counters->increment(v, betweenness[v]);
    }

}

template<typename T, typename C>
std::map<T, C> Brandes<T, C>::get_result() {
    std::map<T, C> result;
    std::map<T, C> counters = counters_.get_counters();
    for (auto &kv : *graph_.get_vertexes()) {
        if (kv.second.has_edges())
            result[kv.first] = counters[kv.first];
    }

    return result;
}