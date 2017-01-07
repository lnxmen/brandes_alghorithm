#include <iostream>
#include <thread>
#include <stack>
#include <unordered_map>
#include "graph.h"
#include "brandes.h"

template<typename T, typename C>
void Brandes<T, C>::run(int threads_number) {
    if (threads_number < 1)
        throw std::invalid_argument("threads number must be positive");
    std::vector<std::thread> threads;

    // run workers
    for (size_t i = 0; i < threads_number-1; i++)
        threads.push_back(std::thread([this] { run_worker(); }));

    run_worker();

    // wait for workers to end their jobs
    for (auto &thread : threads)
        thread.join();
}

template<typename T, typename C>
void Brandes<T, C>::run_worker() {
    IDType *v = manager_.take_job();
    Counters<T, C, false> counters_t;
    while (v != nullptr) {
        // initialize counters
        counters_t.initialize_values(graph_);
        // compute increments for current vertex
        compute(*v, &counters_t);
        // update global counters
        counters_.batch_increment(counters_t.get_counters());
        // get next job (vertex)
        v = manager_.take_job();
    }
}

template<typename T, typename C>
void Brandes<T, C>::compute(IDType s, Counters<T, C, false> *counters) {
    std::stack<IDType> S;
    std::vector<std::vector<IDType>> previous_vertexes;
    std::vector<T> shortest_paths_counter;
    std::vector<T> distance;
    std::vector<C> betweenness;

    for (Vertex &vertex : *graph_.get_vertexes()) {
        shortest_paths_counter.emplace_back(0);
        distance.emplace_back(-1);
        betweenness.emplace_back(0);
        previous_vertexes.emplace_back(std::vector<IDType>());
    }

    shortest_paths_counter[s] = 1;
    distance[s] = 0;

    std::queue<IDType> Q;
    Q.push(s);

    IDType v;
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
    std::map<T, IDType> *ids = graph_.get_vertexes_id();
    std::vector<C> counters = counters_.get_counters();
    std::map<T, C> ordered;

    Vertex *v;
    for (auto &kv : *ids) {
        v = graph_.get_vertex(kv.second);
        if (v->has_edges())
            ordered[kv.first] = counters[kv.second];
    }

    return ordered;
}