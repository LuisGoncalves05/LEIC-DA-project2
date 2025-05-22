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

/**
 * @brief Main function for the Delivery Truck Pallet Packing Optimization project.
 *
 * This function handles the command executed:
 * - transfering control to the command line interface;
 * - calling the wanted knapsack algorithm;
 * - reading the wanted dataset and solving the problem with all algorithms. 
 */
int main(const int argc, char** argv) {  
    if (argc == 1) {
        interface();
    } else if (argc == 3) { // ./program <algorithm> <dataset_no> will use the datasets in data/example_no and output to data/example_no/Solution.txt
        std::string algorithm = argv[1];
        std::string dataset_number = argv[2];
        problem_solver({algorithm, dataset_number});
    } else
        throw std::runtime_error("Invalid usage.");

    return 0;
}
