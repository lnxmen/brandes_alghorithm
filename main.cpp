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

    map<Vertex *, int> counter;
    mutex m;

public:

    void output() {
        for (auto &kv : counter) {
            if (kv.first->edges_out.size() > 0)
                printf("%d %d\n", kv.first->id, kv.second);
        }
    }

    void increment(Vertex* v, int value) {
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
    // BC: pośrednictwo;
    // V: wierzchołki;
    // d[w] odległość do wierzchołka w;
    // sigma[w] liczba najkrótszych ścieżek do wierzchołka w;
    // previous[w] poprzednicy wierzchołka w na wszystkich najkrótszych ścieżkach;
    // delta[v] wartość pośrednictwa dla v w ścieżkach startujących z s.

    stack<Vertex *> S;
    map<Vertex *, std::vector<Vertex *>> previous;
    map<Vertex *, int> sigma;
    map<Vertex *, int> d;
    map<Vertex *, int> delta;

    for (Vertex *w : *vertexes) {
        sigma[w] = 0;
        d[w] = -1;
        delta[w] = 0;
    }

    sigma[s] = 1;
    d[s] = 0;

    queue<Vertex *> Q;
    Q.push(s);

    Vertex *v;
    while (!Q.empty()) {
        v = Q.front();
        Q.pop();
        S.push(v);

        for (Vertex *w : v->edges_out) {
            if (d[w] < 0) {
                Q.push(w);
                d[w] = d[v] + 1;
            }
            if (d[w] == d[v] + 1) {
                sigma[w] += sigma[v];
                previous[w].push_back(v);
            }
        }
    }

    while (!S.empty()) {
        v = S.top();
        S.pop();
        for (Vertex *p : previous[v])
            delta[p] += (sigma[p] / sigma[v]) * (1 + delta[v]);
        if (v != s)
            bc.increment(v, delta[v]);
    }
}

void brandes() {
    vector<Vertex *> V;
    for (auto &kv : graph)
        V.push_back(&kv.second);
    bc.initialize(V);

    thread threads[V.size()];
    int j = 0;
    for (auto v : V)
        threads[j++] = thread(brandes_vertex, v, &V);

    for (int i = 0; i < V.size(); i++)
        threads[i].join();
}

int main() {
    read();
    brandes();
    bc.output();
    return 0;
}

