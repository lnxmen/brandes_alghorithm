#include "graph.h"

template<typename T>
IDType Graph<T>::get_or_insert_vertex(T v) {
    IDType id = get_linked_ID(v);
    if (id >= 0)
        return id;
    id = last_id++;
    vertices.emplace_back(Vertex(id));
    vertices_ids.insert(std::pair<T, IDType>(v, id));
    return id;
}

template<typename T>
IDType Graph<T>::get_linked_ID(T v) {
    auto it = vertices_ids.find(v);
    if (it == vertices_ids.end())
        return -1;
    return (*it).second;
}

template<typename T>
void Graph<T>::connect(T v1, T v2) {
    IDType i1, i2;
    i1 = get_or_insert_vertex(v1);
    i2 = get_or_insert_vertex(v2);
    Vertex *v = get_vertex(i1);
    Vertex *w = get_vertex(i2);
    v->add_edge(w);
}

template<typename T>
Vertex *Graph<T>::get_vertex(IDType v) {
    if (v < vertices.size())
        return &vertices.at(v);
    return nullptr;
}
