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
    IDType v = manager_.take_job();
    Counters<T, C, false> counters_t;
    // initialize counters
    counters_t.initialize_values(graph_);
    while (v > -1) {
        // compute increments for current vertex
        compute(v, &counters_t);
        // get next job (vertex)
        v = manager_.take_job();
    }
    // update global counters
    counters_.batch_increment(counters_t.get_counters());
}

template<typename T, typename C>
void Brandes<T, C>::compute(IDType vertex_id, Counters<T, C, false> *counters) {
    std::stack<IDType> S;
    std::vector<std::vector<IDType>> P;
    std::vector<T> sigma;
    std::vector<T> d;
    std::vector<C> delta;

    for (Vertex &vertex : *graph_.get_vertexes()) {
        sigma.emplace_back(0);
        d.emplace_back(-1);
        delta.emplace_back(0);
        P.emplace_back(std::vector<IDType>());
    }

    sigma[vertex_id] = 1;
    d[vertex_id] = 0;

    std::queue<IDType> Q;
    Q.push(vertex_id);

    IDType v;
    while (!Q.empty()) {
        v = Q.front(); Q.pop();
        S.push(v);

        Vertex *a = graph_.get_vertex(v);
        for (IDType w : *a->get_edges()) {
            if (d[w] < 0) {
                Q.push(w);
                d[w] = d[v] + 1;
            }
            if (d[w] == d[v] + 1) {
                sigma[w] += sigma[v];
                P[w].emplace_back(v);
            }
        }
    }

    while (!S.empty()) {
        v = S.top(); S.pop();
        for (IDType p : P[v])
            delta[p] += (C(sigma[p]) / sigma[v]) * (1.0 + delta[v]);
        if (v != vertex_id)
            counters->increment(v, delta[v]);
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