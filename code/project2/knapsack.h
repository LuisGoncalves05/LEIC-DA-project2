#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>
#include <string>

std::pair<std::vector<int>, std::vector<int>> knapsack(std::vector<int> weights, std::vector<int> profits, int max_weight, std::string& algorithm);

std::pair<std::vector<int>, std::vector<int>> knapsack_bf(std::vector<int> weights, std::vector<int> profits, int max_weight, std::string& algorithm);

std::pair<std::vector<int>, std::vector<int>> knapsack_dp_iterative(std::vector<int> weights, std::vector<int> profits, int max_weight, std::string& algorithm);

std::pair<std::vector<int>, std::vector<int>> knapsack_dp_recursive_vector(std::vector<int> weights, std::vector<int> profits, int max_weight, std::string& algorithm);

std::pair<std::vector<int>, std::vector<int>> knapsack_dp_recursive_map(std::vector<int> weights, std::vector<int> profits, int max_weight, std::string& algorithm);

std::pair<std::vector<int>, std::vector<int>> knapsack_greedy(std::vector<int> weights, std::vector<int> profits, int max_weight, std::string& algorithm);

std::pair<std::vector<int>, std::vector<int>> knapsack_ilp(std::vector<int> weights, std::vector<int> profits, int max_weight, std::string& algorithm);

#endif
