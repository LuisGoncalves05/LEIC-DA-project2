#include <stdexcept>

#include "interface.h"
#include "io.h"
#include "knapsack.h"
#include <iostream>

/**
 * @mainpage
 * This is the documentation for the Delivery Truck Pallet Packing Optimization project.
 */

int main(const int argc, char** argv) {
    std::string path, algorithm;
    
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
    
    unsigned max_weight;
    unsigned num_pallets;

    std::vector<unsigned> weights(num_pallets);
    std::vector<unsigned> profits(num_pallets);

    read_truck(truck_and_pallets_path, max_weight, num_pallets);
    read_pallets(pallets_path, weights, profits);
    
    std::vector<bool> used_pallets = std::move(knapsack(weights, profits, num_pallets, max_weight, algorithm));

    print_output(used_pallets, weights, profits, output_path);

    return 0;
}
