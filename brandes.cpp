#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <queue>
#include <sstream>
#include <mutex>
#include <thread>

using namespace std;

class Vertex {

public:
    int id;
    vector<Vertex *> edges_out;

    Vertex(int id) : id(id) {};

    bool operator<(const Vertex &rhs) const { return (id < rhs.id); }
};


class BetweennessCentrality {

    map<Vertex *, double> counter;
    mutex m;

public:

    void output() {
        for (auto &kv : counter) {
            if (kv.first->edges_out.size() > 0)
                printf("%d %.0f\n", kv.first->id, kv.second);
        }
    }

    void increment(Vertex* v, double value) {
        lock_guard<mutex> guard(m);
        counter[v] += value;
    }

    void initialize(vector<Vertex*> vertexes) {
        for (Vertex* v : vertexes)
            counter[v] = 0;
    };

};

map<int, Vertex> graph;
BetweennessCentrality bc;

bool vertex_exists(int id) {
    return graph.find(id) != graph.end();
}

Vertex *get_vertex(int id) {
    auto it = graph.find(id);
    if (it == graph.end())
        return nullptr;
    return &it->second;
}

void connect(int v1, int v2) {
    if (!vertex_exists(v1))
        graph.insert(pair<int, Vertex>(v1, Vertex(v1)));
    if (!vertex_exists(v2))
        graph.insert(pair<int, Vertex>(v2, Vertex(v2)));
    auto v = &graph.find(v1)->second;
    auto w = get_vertex(v2);
    v->edges_out.push_back(w);
}

void read() {
    int v1, v2;
    string s;
    while (getline(cin, s)) {
        if (s.empty())
            break;
        istringstream line(s);
        line >> v1;
        line >> v2;
        connect(v1, v2);
    }
}

void brandes_vertex(Vertex *s, vector<Vertex *> *vertexes) {
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
        v = S.top(); S.pop();
        for (Vertex *p : previous_vertexes[v])
            betweenness[p] += (shortest_paths_counter[p] / shortest_paths_counter[v]) * (1 + betweenness[v]);
        if (v != s)
            bc.increment(v, betweenness[v]);
    }
}

void brandes() {
    vector<Vertex *> V;
    for (auto &kv : graph)
        V.push_back(&kv.second);
    bc.initialize(V);

    for (auto v : V)
        brandes_vertex(v, &V);
}

int main() {
    read();
    brandes();
    bc.output();
    return 0;
}

