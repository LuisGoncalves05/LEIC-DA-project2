#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>


/**
 * @brief Calls a chosen algorithm to solve the knapsack problem and prints output.
 * @param weights weights of the pallets
 * @param profits profits of the pallets
 * @param num_pallets number of pallets
 * @param max_weight maximum weight of the truck
 * @param algorithm algorithm chosen to solve the problem
 * @return which pallets are part of the solution
 */
std::vector<bool> knapsack(const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned num_pallets, const unsigned max_weight, const std::string& algorithm);

/**
 * @brief Brute-force algorithm to solve the knapsack problem.
 * O(2^n), where n is the number of pallets.
 * @param weights weights of the pallets
 * @param profits profits of the pallets
 * @param num_pallets number of pallets
 * @param max_weight maximum weight of the truck
 * @return which pallets are part of the solution
 */
std::vector<bool> knapsack_bf(const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned num_pallets, const unsigned max_weight);

/**
 * @brief Dynamic programming algorithm to solve the knapsack problem filling the recursion table iteratively.
 * O(n*W), where n is the number of pallets and W is the maximum weight, space and time complexity.
 * @param weights weights of the pallets
 * @param profits profits of the pallets
 * @param num_pallets number of pallets
 * @param max_weight maximum weight of the truck
 * @return which pallets are part of the solution
 */
std::vector<bool> knapsack_dp_iterative(const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned num_pallets, const unsigned max_weight);

/**
 * @brief Dynamic programming algorithm to solve the knapsack problem filling the recursion table recursively.
 * O(n*W), where n is the number of pallets and W is the maximum weight, space and time complexity.
 * @param weights weights of the pallets
 * @param profits profits of the pallets
 * @param num_pallets number of pallets
 * @param max_weight maximum weight of the truck
 * @return which pallets are part of the solution
 */
std::vector<bool> knapsack_dp_recursive_vector(const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned num_pallets, const unsigned max_weight);

/**
 * @brief Helper function for the recursive dynamic programming algorithm.
 * @param item current item (table row)
 * @param weight current weight (table column)
 * @param weights weights of the pallets
 * @param profits profits of the pallets
 * @param last_item_vector recursion table for the last item used
 * @param max_value_vector recursion table for the maximum value
 * @return maximum value for the current item and weight
 */
unsigned dp_recursive_vector_helper(const unsigned item, const unsigned weight, const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, std::vector<std::vector<unsigned>>& last_item_vector, std::vector<std::vector<unsigned>>& max_value_vector);

/**
 * @brief Dynamic programming algorithm to solve the knapsack problem using a map to store the recursion table.
 * O(n*W), where n is the number of pallets and W is the maximum weight, space and time complexity.
 * @param weights weights of the pallets
 * @param profits profits of the pallets
 * @param num_pallets number of pallets
 * @param max_weight maximum weight of the truck
 * @return which pallets are part of the solution
 */
std::vector<bool> knapsack_dp_recursive_map(const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned num_pallets, const unsigned max_weight);


/**
 * @brief Helper function for the recursive dynamic programming algorithm using a map that calculates the index for a recursion table position.
 * @param i current item (table row)
 * @param j current weight (table column)
 * @param max_weight maximum weight of the truck
 * @return map key for the recursion table position 
 */
inline unsigned to_flat_idx(const unsigned i, const unsigned j, const unsigned max_weight);

/**
 * @brief Helper function for the recursive dynamic programming algorithm using a map.
 * @param item current item (table row)
 * @param weight current weight (table column)
 * @param weights weights of the pallets
 * @param profits profits of the pallets
 * @param max_weight maximum weight of the truck
 * @param last_item_map recursion table for the last item used in a map
 * @param max_value_map recursion table for the maximum value in a map
 * @return maximum value for the current item and weight
 */
unsigned dp_recursive_map_helper(const unsigned item, const unsigned weight, const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned max_weight, std::unordered_map<unsigned, unsigned>& last_item_map, std::unordered_map<unsigned, unsigned>& max_value_map);

/**
 * @brief Greedy algorithm to solve the knapsack problem.
 * O()
 * @param weights weights of the pallets
 * @param profits profits of the pallets
 * @param num_pallets number of pallets
 * @param max_weight maximum weight of the truck
 * @return which pallets are part of the solution
 */
std::vector<bool> knapsack_greedy(const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned num_pallets, const unsigned max_weight);

/**
 * @brief Integer linear programming algorithm to solve the knapsack problem
 * @param weights weights of the pallets
 * @param profits profits of the pallets
 * @param num_pallets number of pallets
 * @param max_weight maximum weight of the truck
 * @return which pallets are part of the solution
 */
std::vector<bool> knapsack_ilp(const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned num_pallets, const unsigned max_weight);

#endif
