#include "measure_time.h"
#include "tsp.h"

Graph random_graph(int size) {
    Graph graph;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution_distance(10, 100);

    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            graph.add_edge(i, j, distribution_distance(generator) / 10.0);
        }
    }

    int additional_edges = random_number(size);

    for (int i = 0; i < additional_edges; ++i) {
        int vertex_1 = random_number(size);
        int vertex_2 = random_number(size);
        if (vertex_1 != vertex_2 && graph.has_edge(vertex_1, vertex_2)) {
            graph.remove_edge(vertex_1, vertex_2);
        }
    }

    return graph;
}

int random_number(int size) {
    srand(time(NULL));
    return rand() % size;
}

void measure_time_test() {
    double time_stop = 3;
    double time1 = 0;
    double time2 = 0;
    double time3 = 0;
    int N = 3;
    do {
        Graph graph = random_graph(N);

        auto t1 = std::chrono::high_resolution_clock::now(); // Record time before executing the algorithm
        std::vector<int> result = tsp_permutations(graph);
        std::cout << Length(result,graph) << std::endl;
        auto t2 = std::chrono::high_resolution_clock::now(); // Record time after executing the algorithm
        time1 = std::chrono::duration<double>(t2 - t1).count(); // Calculate the time difference
        std::cout << "tsp_permutations: " << "N = " << N << ", " << "time = " << time1 << " seconds" << std::endl;

        t1 = std::chrono::high_resolution_clock::now(); // Record time before executing the algorithm
        result = tsp_branches(graph);
        std::cout << Length(result, graph) << std::endl;
        t2 = std::chrono::high_resolution_clock::now(); // Record time after executing the algorithm
        time2 = std::chrono::duration<double>(t2 - t1).count(); // Calculate the time difference
        std::cout << "tsp_branches: " << "N = " << N << ", " << "time = " << time2 << " seconds" << std::endl;

        t1 = std::chrono::high_resolution_clock::now(); // Record time before executing the algorithm
        result = tsp_greedy(graph);
        std::cout << Length(result, graph) << std::endl;
        t2 = std::chrono::high_resolution_clock::now(); // Record time after executing the algorithm
        time3 = std::chrono::duration<double>(t2 - t1).count(); // Calculate the time difference
        std::cout << "tsp_greedy: " << "N = " << N << ", " << "time = " << time3 << " seconds" << std::endl;
        std::cout << "---------------------------------" << std::endl;
        N += 1;
    } while (time1 < time_stop && time2 < time_stop && time3 < time_stop);
}

void test(){
    Graph g {{0,1,1},{1,2,2},{2,3,3},{1,3,4},{0,2,7},{0,3,10}};
    std::vector<int> result = tsp_permutations(g);
    for (int i = 0; i < result.size(); i++) {
        if (i != 0) {
            std::cout << ", ";
        }
        std::cout << result[i] << "\n";
    }
    std::vector<int> result2 = tsp_branches(g);
    for (int i = 0; i < result2.size(); i++) {
        if (i != 0) {
            std::cout << ", ";
        }
        std::cout << result2[i] << "\n";
    }
    std::vector<int> result3 = tsp_greedy(g);
    for (int i = 0; i < result3.size(); i++) {
        if (i != 0) {
            std::cout << ", ";
        }
        std::cout << result3[i];
    }
    
}