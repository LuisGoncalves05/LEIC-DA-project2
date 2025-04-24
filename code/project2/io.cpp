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

    for (int i = 0; i < weights.size(); i++) {
        std::getline(inputFile, line);
        std::getline(inputFile, pallet, ',');
        std::getline(inputFile, weight, ',');
        std::getline(inputFile, profit);

        weights[i] = std::stoul(weight);
        profits[i] = std::stoul(profit);
    }

    inputFile.close();
}

void write_output(std::vector<bool>& used_pallets, std::vector<unsigned>& weights, std::vector<unsigned>& profits, std::string& output_path) {
    std::ofstream outputFile(output_path + "Solution.csv");
    if (!outputFile.is_open()) throw std::runtime_error("Error: Could not create output file.");

    outputFile << "Pallet,\tWeight,\tProfit\n";

    unsigned int total_weight = 0, total_profit = 0;
    for (unsigned i = 0; i < used_pallets.size(); i++) {
        if (used_pallets[i]) {
            total_weight += weights[i];
            total_profit += profits[i];
            outputFile << i + 1 << ",\t" << weights[i] << ",\t" << profits[i] << '\n';
        }
    }
    outputFile << "\nTotal weight: " << total_weight << "\n";
    outputFile << "Total profit: " << total_profit << "\n";

    outputFile.close();
}

void print_output(std::vector<bool>& used_pallets, std::vector<unsigned>& weights, std::vector<unsigned>& profits) {
    std::cout << "Used pallets:\n";
    unsigned int total_weight = 0, total_profit = 0;
    for (unsigned i = 0; i < used_pallets.size(); i++) {
        if (used_pallets[i]) {
            total_weight += weights[i];
            total_profit += profits[i];
            std::cout << "1 ";
        } else std::cout << "0 ";
    }
    std::cout << "\nTotal weight: " << total_weight << "\n";
    std::cout << "Total profit: " << total_profit << "\n";
}
