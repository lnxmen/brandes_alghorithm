#ifndef BRANDES_BRANDES_H
#define BRANDES_BRANDES_H

#include <map>
#include <mutex>
#include "graph.h"
#include "manager.h"
#include "counters.h"

template<typename T>
class Brandes {

    using cType = double;

    Graph<T> &graph_;
    Manager<T> manager_;
    Counters<T, cType, true> &counters_;

public:

    Brandes(Graph<T> &graph) : graph_(graph) {
        manager_.add_jobs(graph.get_vertexes_ids());
        counters_(graph.get_vertexes_ids());
    }

    void run(int threads);

private:

    void run_worker();

};

//    {
//
//    }
/*
 private:

    void compute(Vertex *s, vector<Vertex *> *vertexes) {
        stack<Vertex *> S;
        map<Vertex *, std::vector<Vertex *>> previous_vertexes;
        map<Vertex *, double> shortest_paths_counter;
        map<Vertex *, double> distance;
        map<Vertex *, double> betweenness;

        for (Vertex *w : *vertexes) {
            shortest_paths_counter[w] = 0;
            distance[w] = -1;
            betweenness[w] = 0;
        }

        shortest_paths_counter[s] = 1;
        distance[s] = 0;

        queue<Vertex *> Q;
        Q.push(s);

        Vertex *v;
        while (!Q.empty()) {
            v = Q.front();
            Q.pop();
            S.push(v);

            for (Vertex *w : v->edges_out) {
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
            for (Vertex *p : previous_vertexes[v])
                betweenness[p] += (shortest_paths_counter[p] / shortest_paths_counter[v]) * (1 + betweenness[v]);
            if (v != s)
                bc.increment(v, betweenness[v]);
        }
    }
 */

template class Brandes<int>;

#endif //BRANDES_BRANDES_H
