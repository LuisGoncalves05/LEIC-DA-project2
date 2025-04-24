#include <stdexcept>
#include <set>
#include <climits>
#include <unordered_map>

#include "knapsack.h"
#include <bitset>
#include <iostream>


constexpr unsigned INVALID_RESULT = UINT_MAX;

const std::set<std::string> valid_algorithms = {
    "bf", "dp_iterative", "dp_recursive_vector", "dp_recursive_map", "greedy", "ilp"
};


std::vector<bool> knapsack(const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned num_pallets, const unsigned max_weight, const std::string& algorithm) {
    if (valid_algorithms.find(algorithm) == valid_algorithms.end()) {
        throw std::runtime_error("Unknown algorithm specified: " + algorithm + ".");
    }

    if (algorithm == "bf") {
        return knapsack_bf(weights, profits, num_pallets, max_weight);
    } else if (algorithm == "dp_iterative") {
        return knapsack_dp_iterative(weights, profits, num_pallets, max_weight);
    } else if (algorithm == "dp_recursive_vector") {
        return knapsack_dp_recursive_vector(weights, profits, num_pallets, max_weight);
    } else if (algorithm == "dp_recursive_map") {
        return knapsack_dp_recursive_map(weights, profits, num_pallets, max_weight);
    } else if (algorithm == "greedy") {
        return knapsack_greedy(weights, profits, num_pallets, max_weight);
    } else if (algorithm == "ilp") {
        return knapsack_ilp(weights, profits, num_pallets, max_weight);
    } else {
        throw std::runtime_error("Invalid algorithm specified.");
    }
}


std::vector<bool> knapsack_bf(const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned num_pallets, const unsigned max_weight) {
    if (num_pallets > 32) {
        throw std::runtime_error("That is a bit ambitious don't you think?");
    }

    std::vector<bool> used_pallets(num_pallets, false);
    
    unsigned combination = 0;
    unsigned best = 0;
    unsigned best_combination = INVALID_RESULT;
    while (combination < (1<<num_pallets)) {
        std::bitset<32> combinations(combination);
        unsigned value = 0;
        unsigned weight = 0;
        for (unsigned j = 0; j < num_pallets; j++) {
            weight += weights[j] * combinations[j];
            value += profits[j] * combinations[j];
            if (weight > max_weight) 
                break;

            if (value > best) {
                best_combination = combination;
                best = value;
            }
        }
        combination++;
    }

    const std::bitset<32> b(best_combination);
    if (best_combination != INVALID_RESULT) {
        for (int j = 0; j < num_pallets; j++) {
            used_pallets[j] = b[j];
        }
    }
    
    return used_pallets;
}


std::vector<bool> knapsack_dp_iterative(const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned num_pallets, const unsigned max_weight) {
    std::vector<bool> used_pallets(num_pallets, false);
    
    //TODO
    
    return used_pallets;
}


std::vector<bool> knapsack_dp_recursive_vector(const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned num_pallets, const unsigned max_weight) {
    std::vector<bool> used_pallets(num_pallets, false);
    
    unsigned item = num_pallets;
    unsigned weight = max_weight;

    std::vector<std::vector<unsigned>> last_item_vector(num_pallets + 1, std::vector<unsigned>(max_weight + 1, INVALID_RESULT)),
                                       max_value_vector(num_pallets + 1, std::vector<unsigned>(max_weight + 1, INVALID_RESULT));
    const unsigned max_value = dp_recursive_vector_helper(item, weight, weights, profits, last_item_vector, max_value_vector);

    if (max_value == INVALID_RESULT)
        return used_pallets;

    while (item > 0 && weight > 0) {
        if (last_item_vector[item][weight] != weight) {
            used_pallets[item - 1] = true;
            weight = last_item_vector[item][weight];
        }
        item--;
    }

    return used_pallets;
}

unsigned dp_recursive_vector_helper(const unsigned item, const unsigned weight, const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, std::vector<std::vector<unsigned>>& last_item_vector, std::vector<std::vector<unsigned>>& max_value_vector) {
    if (max_value_vector[item][weight] == INVALID_RESULT) {
        if (item == 0 || weight == 0) {
            max_value_vector[item][weight] = 0;
        } else {
            unsigned used = INVALID_RESULT;

            // Check if called with non-negative weight
            if (weights[item - 1] <= weight) {
                used = dp_recursive_vector_helper(item - 1, weight - weights[item - 1], weights, profits, last_item_vector, max_value_vector);
                if (used != INVALID_RESULT)
                    used += profits[item - 1];
            }

            const unsigned not_used = dp_recursive_vector_helper(item - 1, weight, weights, profits, last_item_vector, max_value_vector);

            if (used != INVALID_RESULT && used > not_used) {
                last_item_vector[item][weight] = weight - weights[item - 1];
                max_value_vector[item][weight] = used;
            } else {
                last_item_vector[item][weight] = weight;
                max_value_vector[item][weight] = not_used;
            }
        }
    }

    return max_value_vector[item][weight];
}


std::vector<bool> knapsack_dp_recursive_map(const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned num_pallets, const unsigned max_weight) {
    std::vector<bool> used_pallets(num_pallets, false);
    
    unsigned item = num_pallets;
    unsigned weight = max_weight;

    std::unordered_map<unsigned, unsigned> last_item_map, max_value_map;
    const unsigned max_value = dp_recursive_map_helper(item, weight, weights, profits, max_weight, last_item_map, max_value_map);

    if (max_value == INVALID_RESULT)
        return used_pallets;


    while (item > 0 && weight > 0) {
        unsigned flat_index = to_flat_idx(item, weight, max_weight);
        if (last_item_map.count(flat_index) == 0)
            break;

        const unsigned li_w = last_item_map[flat_index];
        if (li_w != weight) {
            used_pallets[item - 1] = true;
            weight = li_w;
        }
        item--;
    }

    return used_pallets;
}

inline unsigned to_flat_idx(const unsigned combination, const unsigned j, const unsigned max_weight) {
    return combination * (max_weight + 1) + j;
}

unsigned dp_recursive_map_helper(const unsigned item, const unsigned weight, const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned max_weight, std::unordered_map<unsigned, unsigned>& last_item_map, std::unordered_map<unsigned, unsigned>& max_value_map) {
    const unsigned flat_index = to_flat_idx(item, weight, max_weight);

    if (max_value_map.count(flat_index) == 0) {
        if (item == 0 || weight == 0) {
            max_value_map[flat_index] = 0;
        } else {
            unsigned used = INVALID_RESULT;

            // Check if called with non-negative weight
            if (weights[item - 1] <= weight) {
                used = dp_recursive_map_helper(item - 1, weight - weights[item - 1], weights, profits, max_weight, last_item_map, max_value_map);
                if (used != INVALID_RESULT)
                    used += profits[item - 1];
            }

            const unsigned not_used = dp_recursive_map_helper(item - 1, weight, weights, profits, max_weight, last_item_map, max_value_map);

            if (used != INVALID_RESULT && used > not_used) {
                last_item_map[flat_index] = weight - weights[item - 1];
                max_value_map[flat_index] = used;
            } else {
                last_item_map[flat_index] = weight;
                max_value_map[flat_index] = not_used;
            }
        }
    }

    return max_value_map[flat_index];
}



std::vector<bool> knapsack_greedy(const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned num_pallets, const unsigned max_weight) {
    std::vector<bool> used_pallets(num_pallets, false);
    
    
    
    return used_pallets;
}


std::vector<bool> knapsack_ilp(const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned num_pallets, const unsigned max_weight) {
    std::vector<bool> used_pallets(num_pallets, false);
    
    //TODO
    
    return used_pallets;
}