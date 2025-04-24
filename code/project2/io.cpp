#include "io.h"

void read_truck(const std::string& input_file, unsigned &max_weights, unsigned &num_pallets) {
    std::ifstream inputFile(input_file);
    if (!inputFile.is_open()) throw std::runtime_error("Error: Could not open input file.");

    std::string line, capacity, pallets;
    std::getline(inputFile, line); // skip first line
    std::getline(inputFile, capacity, ',');
    std::getline(inputFile, pallets);

    max_weights = std::stoul(capacity);
    num_pallets = std::stoul(pallets);

    inputFile.close();
}

void read_pallets(const std::string& input_file, std::vector<unsigned> &weights, std::vector<unsigned> &profits) {
    std::ifstream inputFile(input_file);
    if (!inputFile.is_open()) throw std::runtime_error("Error: Could not open input file.");

    std::string line, pallet, weight, profit;

    for (int i = 1; i < weights.size(); i++) {
        std::getline(inputFile, line);
        std::getline(inputFile, pallet, ',');
        std::getline(inputFile, weight, ',');
        std::getline(inputFile, profit);

        weights[i] = std::stoul(weight);
        profits[i] = std::stoul(profit);
    }

    inputFile.close();
}

void print_output(std::vector<bool>& used_pallets, std::vector<unsigned>& weights, std::vector<unsigned>& profits, std::string& output_path) {

    //TODO

}
