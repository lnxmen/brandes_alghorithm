#ifndef BRANDES_GRAPH_H
#define BRANDES_GRAPH_H

#include <vector>
#include <map>

template<typename T>
class Vertex {
    T id_;
    std::vector<T> edges_;

public:

    Vertex(T id) : id_(id) {}

    void add_edge(Vertex<T> *v) { edges_.push_back(v->id_); }

    std::vector<T> get_edges() { return edges_; }

    bool has_edges() { return !edges_.empty(); }

    T get_id() { return id_; }
};


template<typename T>
class Graph {
    std::map<T, Vertex<T>> vertices;
    std::vector<T> vertices_ids;

public:

    Vertex<T> *get_vertex(T v);

    void add_vertex(T v);

    void connect(T v1, T v2);

    std::vector<T> *get_vertexes_ids() { return &vertices_ids; };

    std::map<T, Vertex<T>> *get_vertexes() { return &vertices; };

    bool vertex_exists(T v) { return vertices.find(v) != vertices.end(); }
};

template
class Graph<int>;

#endif //BRANDES_GRAPH_H
