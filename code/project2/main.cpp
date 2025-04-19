#include <stdexcept>

#include "interface.h"
#include "io.h"
#include "knapsack.h"

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
    
    auto [max_weight, num_pallets] = std::move(read_truck(truck_and_pallets_path));
    auto [weights, profits] = std::move(read_pallets(pallets_path, num_pallets));
    auto [result_weights, result_profits] = std::move(knapsack(weights, profits, max_weight, algorithm));

    print_output(result_weights, result_profits, output_path);
    
    return 0;
}
