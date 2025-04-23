#include "io.h"

#include <fstream>
#include <vector>

void read_truck(const std::string& input_file, unsigned &max_weights, unsigned &num_pallets) {
    std::ifstream inputFile(input_file);
    if (!inputFile.is_open()) throw std::runtime_error("Error: Could not open input file.");

    
    //TODO

    inputFile.close();
}

void read_pallets(const std::string& input_file, std::vector<unsigned> &weights, std::vector<unsigned> &profits) {
    std::ifstream inputFile(input_file);
    if (!inputFile.is_open()) throw std::runtime_error("Error: Could not open input file.");

    
    //TODO

    inputFile.close();
}

void print_output(std::vector<bool>& used_pallets, std::vector<unsigned>& weights, std::vector<unsigned>& profits, std::string& output_path) {

    //TODO

}
