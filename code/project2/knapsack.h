#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

std::vector<bool> knapsack(const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned num_pallets, const unsigned max_weight, const std::string& algorithm);

std::vector<bool> knapsack_bf(const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned num_pallets, const unsigned max_weight);

std::vector<bool> knapsack_dp_iterative(const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned num_pallets, const unsigned max_weight);

std::vector<bool> knapsack_dp_recursive_vector(const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned num_pallets, const unsigned max_weight);

unsigned dp_recursive_vector_helper(const unsigned item, const unsigned weight, const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, std::vector<std::vector<unsigned>>& last_item_vector, std::vector<std::vector<unsigned>>& max_value_vector);

std::vector<bool> knapsack_dp_recursive_map(const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned num_pallets, const unsigned max_weight);

inline unsigned to_flat_idx(const unsigned i, const unsigned j, const unsigned max_weight);

unsigned dp_recursive_map_helper(const unsigned item, const unsigned weight, const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned max_weight, std::unordered_map<unsigned, unsigned>& last_item_map, std::unordered_map<unsigned, unsigned>& max_value_map);

std::vector<bool> knapsack_greedy(const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned num_pallets, const unsigned max_weight);

std::vector<bool> knapsack_ilp(const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned num_pallets, const unsigned max_weight);

#endif
