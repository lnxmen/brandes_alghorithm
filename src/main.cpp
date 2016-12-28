#include <iostream>
#include <sstream>
#include <fstream>
#include "brandes.h"

template<typename T>
void read(std::ifstream &input, Graph<T> *graph) {
    T v1, v2;
    std::string s;
    while (getline(input, s)) {
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

    std::ifstream in_file;
    in_file.open(argv[2]);
    read(in_file, &graph);
    in_file.close();

    Brandes<int, double> brandes(graph);
    brandes.run(std::stoi(argv[1]));

    std::ofstream out_file;
    out_file.open(argv[3]);
    for (auto &kv : brandes.get_result())
        out_file << kv.first << " " << kv.second << std::endl;
    out_file.close();

    return 0;
}

