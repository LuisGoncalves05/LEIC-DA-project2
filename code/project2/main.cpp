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
    std::string path, algorithm;
    /*
    if (argc == 1) {
        start_cli();
        return 0;
    } else if (argc == 2) { // ./program <algorithm> will use the datasets in IO and output to IO/Solution.txt
        path = "io/";
        algorithm = argv[1];
    } else if (argc == 3) { // ./program <dataset_no> <algorithm> will use the datasets in data/example_no and output to data/example_no/Solution.txt
        std::string dataset_number = argv[1];
        path = "data/example" + dataset_number + "/";
        algorithm = argv[2];
    } else 
        throw std::runtime_error("Invalid usage.");

    std::string pallets_path = path + "Pallets.csv";
    std::string truck_and_pallets_path = path + "TruckAndPallets.csv";
    std::string output_path = path + "Solution.txt";
    
    auto [max_weight, num_pallets] = std::move(read_truck(truck_and_pallets_path));
    auto [weights, profits] = std::move(read_pallets(pallets_path, num_pallets));
    auto used_pallets = std::move(knapsack(weights, profits, num_pallets, max_weight, algorithm));

    print_output(used_pallets, weights, profits, output_path);
    */
    
    std::vector<unsigned> weights = {6000, 5000, 400, 300, 50, 300, 20};
    std::vector<unsigned> profits = {100, 200, 300, 40, 400, 100, 70};
    
    auto start = std::chrono::high_resolution_clock::now();

    auto used_pallets = std::move(knapsack_bf(weights, profits, weights.size(), 1000));

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Bf: " << duration.count() << " seconds.\n";
    for (auto element: used_pallets) std::cout << element << ' ';
    std::cout << std::endl;

    start = std::chrono::high_resolution_clock::now();

    used_pallets = std::move(knapsack_dp_recursive_vector(weights, profits, weights.size(), 1000));

    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Vec: " << duration.count() << " seconds.\n";
    for (auto element: used_pallets) std::cout << element << ' ';
    std::cout << std::endl;

    start = std::chrono::high_resolution_clock::now();

    used_pallets = std::move(knapsack_dp_recursive_map(weights, profits, weights.size(), 1000));

    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Map: " << duration.count() << " seconds.\n";
    for (auto element: used_pallets) std::cout << element << ' ';
    std::cout << std::endl;

    return 0;
}
