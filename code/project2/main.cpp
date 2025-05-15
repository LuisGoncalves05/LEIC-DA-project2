#include <stdexcept>
#include <iostream>
#include <chrono>

#include "interface.h"
#include "io.h"
#include "knapsack.h"

/**
 * @mainpage
 * This is the documentation for the Delivery Truck Pallet Packing Optimization project.
 */

int main(const int argc, char** argv) {
    std::string path = "io/", algorithm;
    
    if (argc == 2) { // ./program <algorithm> will use the datasets in IO and output to IO/Solution.txt
        algorithm = argv[1];
        if (algorithm == "cli") {
            interface();
            return 0;
        }
    } else if (argc == 3) { // ./program <dataset_no> <algorithm> will use the datasets in data/example_no and output to data/example_no/Solution.txt
        std::string dataset_number = argv[1];
        path = "data/example" + dataset_number + "/";
        algorithm = argv[2];
    } else if (argc > 3)
        throw std::runtime_error("Invalid usage.");

    std::string pallets_path = path + "Pallets.csv";
    std::string truck_and_pallets_path = path + "TruckAndPallets.csv";
    std::string output_path = path + "Solution.txt";

    unsigned max_weight;
    unsigned num_pallets;

    read_truck(truck_and_pallets_path, max_weight, num_pallets);
    
    std::vector<unsigned> weights(num_pallets);
    std::vector<unsigned> profits(num_pallets);
    std::cout << "Reading " << num_pallets << " pallets...\n";
    read_pallets(pallets_path, weights, profits);

    auto start = std::chrono::high_resolution_clock::now();

    auto used_pallets = std::move(knapsack_bf(weights, profits, num_pallets, max_weight));

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Bf: " << duration.count() << " seconds.\n";
    for (auto element: used_pallets) std::cout << element << ' ';
    std::cout << std::endl;

    start = std::chrono::high_resolution_clock::now();

    used_pallets = std::move(knapsack_dp_iterative(weights, profits, num_pallets, max_weight));

    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "It: " << duration.count() << " seconds.\n";
    for (auto element: used_pallets) std::cout << element << ' ';
    std::cout << std::endl;

    start = std::chrono::high_resolution_clock::now();

    used_pallets = std::move(knapsack_dp_recursive_vector(weights, profits, num_pallets, max_weight));

    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Vec: " << duration.count() << " seconds.\n";
    for (auto element: used_pallets) std::cout << element << ' ';
    std::cout << std::endl;

    start = std::chrono::high_resolution_clock::now();

    used_pallets = std::move(knapsack_dp_recursive_map(weights, profits, num_pallets, max_weight));

    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Map: " << duration.count() << " seconds.\n";
    for (auto element: used_pallets) std::cout << element << ' ';
    std::cout << std::endl;

    start = std::chrono::high_resolution_clock::now();

    used_pallets = std::move(knapsack_ilp(weights, profits, num_pallets, max_weight));

    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Ilp: " << duration.count() << " seconds.\n";
    for (auto element: used_pallets) std::cout << element << ' ';
    std::cout << std::endl;

    start = std::chrono::high_resolution_clock::now();

    used_pallets = std::move(knapsack_greedy(weights, profits, num_pallets, max_weight));

    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "greedy: " << duration.count() << " seconds.\n";
    for (auto element: used_pallets) std::cout << element << ' ';
    std::cout << std::endl;

    return 0;
}
