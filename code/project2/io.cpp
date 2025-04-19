#include "io.h"

#include <fstream>
#include <vector>


std::pair<std::vector<int>, std::vector<int>> read_pallets(const std::string& input_file) {
    std::ifstream inputFile(input_file);
    if (!inputFile.is_open())
        throw std::runtime_error("Error: Could not open input file.");

    std::vector<int> weights, profits; 
    
    //TODO

    inputFile.close();

    return std::make_pair(weights, profits);
}


std::pair<int, int> read_truck(const std::string& input_file) {
    std::ifstream inputFile(input_file);
    if (!inputFile.is_open())
        throw std::runtime_error("Error: Could not open input file.");

    int max_weight, max_pallets; 
    
    //TODO

    inputFile.close();

    return std::make_pair(max_weight, max_pallets);
}


void print_output(std::vector<int>& result_weights, std::vector<int>& result_profits, std::string& output_path) {

    //TODO

}
