#include <stdexcept>
#include <set>

#include "knapsack.h"


const std::set<std::string> valid_algorithms = {
    "bf", "dp_iterative", "dp_recursive_vector", "dp_recursive_map", "greedy", "ilp"
};

std::pair<std::vector<int>, std::vector<int>> knapsack(std::vector<int> weights, std::vector<int> profits, int max_weight, int max_pallets, std::string& algorithm) {
    if (valid_algorithms.find(algorithm) == valid_algorithms.end()) {
        throw std::runtime_error("Unknown algorithm specified: " + algorithm + ".");
    }

    std::vector<int> result_weights, result_profits; 
    
    if (algorithm == "bf") {
        return knapsack_bf(weights, profits, max_weight, max_pallets, algorithm);
    } else if (algorithm == "dp_iterative") {
        return knapsack_dp_iterative(weights, profits, max_weight, max_pallets, algorithm);
    } else if (algorithm == "dp_recursive_vector") {
        return knapsack_dp_recursive_vector(weights, profits, max_weight, max_pallets, algorithm);
    } else if (algorithm == "dp_recursive_map") {
        return knapsack_dp_recursive_map(weights, profits, max_weight, max_pallets, algorithm);
    } else if (algorithm == "greedy") {
        return knapsack_greedy(weights, profits, max_weight, max_pallets, algorithm);
    } else if (algorithm == "ilp") {
        return knapsack_ilp(weights, profits, max_weight, max_pallets, algorithm);
    } else {
        throw std::runtime_error("Invalid algorithm specified.");
    }
}


std::pair<std::vector<int>, std::vector<int>> knapsack_bf(std::vector<int> weights, std::vector<int> profits, int max_weight, int max_pallets, std::string& algorithm) {
    std::vector<int> result_weights, result_profits; 
    
    //TODO

    return std::make_pair(std::move(result_weights), std::move(result_profits));
}


std::pair<std::vector<int>, std::vector<int>> knapsack_dp_iterative(std::vector<int> weights, std::vector<int> profits, int max_weight, int max_pallets, std::string& algorithm) {
    std::vector<int> result_weights, result_profits; 
    
    //TODO
    
    return std::make_pair(std::move(result_weights), std::move(result_profits));
}


std::pair<std::vector<int>, std::vector<int>> knapsack_dp_recursive_vector(std::vector<int> weights, std::vector<int> profits, int max_weight, int max_pallets, std::string& algorithm) {
    std::vector<int> result_weights, result_profits; 
    
    //TODO
    
    return std::make_pair(std::move(result_weights), std::move(result_profits));
}


std::pair<std::vector<int>, std::vector<int>> knapsack_dp_recursive_map(std::vector<int> weights, std::vector<int> profits, int max_weight, int max_pallets, std::string& algorithm) {
    std::vector<int> result_weights, result_profits; 
    
    //TODO
    
    return std::make_pair(std::move(result_weights), std::move(result_profits));
}


std::pair<std::vector<int>, std::vector<int>> knapsack_greedy(std::vector<int> weights, std::vector<int> profits, int max_weight, int max_pallets, std::string& algorithm) {
    std::vector<int> result_weights, result_profits; 
    
    //TODO
    
    return std::make_pair(std::move(result_weights), std::move(result_profits));
}


std::pair<std::vector<int>, std::vector<int>> knapsack_ilp(std::vector<int> weights, std::vector<int> profits, int max_weight, int max_pallets, std::string& algorithm) {
    std::vector<int> result_weights, result_profits; 
    
    //TODO
    
    return std::make_pair(std::move(result_weights), std::move(result_profits));
}