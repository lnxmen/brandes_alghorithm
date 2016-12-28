#include <iostream>
#include <sstream>
#include <fstream>
#include "brandes.h"

template<typename T>
void read(char input_filename[], Graph<T> *graph) {
    std::ifstream input_file;
    input_file.open(input_filename);

    T v1, v2;
    std::string s;
    while (getline(input_file, s)) {
        if (s.empty())
            break;
        std::istringstream line(s);
        line >> v1;
        line >> v2;
        graph->connect(v1, v2);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Error: invalid arguments." << std::endl;
        std::cout << "Example: ./brandes threads-number input-file output-file." << std::endl;
        return -1;
    }

    Graph<int> graph;
    read(argv[2], &graph);

    Brandes<int> brandes(graph);
    brandes.run(2);

    for (auto &kv : brandes.get_result()) {
        std::cout << kv.first << " " << kv.second << std::endl;
    }

    return 0;
}

