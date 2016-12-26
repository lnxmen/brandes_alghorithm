#ifndef BRANDES_GRAPH_H
#define BRANDES_GRAPH_H

#include <vector>
#include <map>

template<typename T>
class Vertex {
    T id_;
    std::vector<Vertex<T>*> edges_;

public:

    Vertex(T id) : id_(id) {}

    void add_edge(Vertex<T>* v) { edges_.push_back(v); }
    const std::vector<Vertex<T>*> get_edges() { return edges_; }
    const T get_id() { return id_; }
};


template<typename T>
class Graph {
    std::map<T, Vertex<T>> vertices;
    std::vector<T> vertices_ids;

public:

    void connect(T v1, T v2);
    Vertex<T> *get_vertex(T v);

    void add_vertex(T v);
    bool vertex_exists(T v) { return vertices.find(v) != vertices.end(); }
    const std::vector<T> &get_vertexes_ids() { return vertices_ids; };
    const std::map<T, Vertex<T>> &get_vertexes() { return vertices; };
};

template class Graph<int>;

#endif //BRANDES_GRAPH_H
