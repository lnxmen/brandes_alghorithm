#include "graph.h"

template<typename T>
void Graph<T>::add_vertex(T v) {
    vertices.insert(std::pair<T, Vertex<T>>(v, Vertex<T>(v)));
    vertices_ids.push_back(v);
}

template<typename T>
void Graph<T>::connect(T v1, T v2) {
    if (!vertex_exists(v1))
        add_vertex(v1);
    if (!vertex_exists(v2))
        add_vertex(v2);

    auto v = &vertices.find(v1)->second;
    auto w = get_vertex(v2);
    v->add_edge(w);
}

template<typename T>
Vertex<T> *Graph<T>::get_vertex(T v) {
    auto it = vertices.find(v);
    if (it == vertices.end())
        return nullptr;
    return &it->second;
}
