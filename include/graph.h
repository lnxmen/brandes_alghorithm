#ifndef BRANDES_GRAPH_H
#define BRANDES_GRAPH_H

#include <vector>
#include <map>

using IDType = int;

class Vertex {

    IDType id_;
    std::vector<IDType> edges_;

public:

    Vertex(IDType id) : id_(id) {}

    void add_edge(Vertex *v) { edges_.push_back(v->id_); }

    std::vector<IDType> get_edges() { return edges_; }

    bool has_edges() { return !edges_.empty(); }

    IDType get_id() { return id_; }
};


template<typename T>
class Graph {

    IDType last_id = 0;
    std::vector<Vertex> vertices;
    std::map<T, IDType> vertices_ids;

public:

    Vertex *get_vertex(IDType v);

    IDType get_or_insert_vertex(T v);

    void connect(T v1, T v2);

    std::vector<Vertex> *get_vertexes() { return &vertices; };

    std::map<T, IDType> *get_vertexes_id() { return &vertices_ids; };

    IDType get_linked_ID(T v);

    bool vertex_exists(T v);
};

template
class Graph<int>;

#endif //BRANDES_GRAPH_H
