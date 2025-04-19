#include "io.h"

#include <fstream>
#include <vector>


std::pair<std::vector<unsigned>, std::vector<unsigned>> read_pallets(const std::string& input_file, const unsigned num_pallets) {
    std::ifstream inputFile(input_file);
    if (!inputFile.is_open())
        throw std::runtime_error("Error: Could not open input file.");

    std::vector<unsigned> weights, profits; 
    
    //TODO

    inputFile.close();

    return std::make_pair(weights, profits);
}


std::pair<unsigned, unsigned> read_truck(const std::string& input_file) {
    std::ifstream inputFile(input_file);
    if (!inputFile.is_open())
        throw std::runtime_error("Error: Could not open input file.");

    unsigned max_weight, max_pallets; 
    
    //TODO

    inputFile.close();

    return std::make_pair(max_weight, max_pallets);
}


void print_output(std::vector<bool>& used_pallets, std::vector<unsigned>& weights, std::vector<unsigned>& profits, std::string& output_path) {

    //TODO

}
