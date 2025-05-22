#include <stdexcept>
#include <set>
#include <climits>
#include <unordered_map>
#include <memory>
#include "ortools/linear_solver/linear_solver.h"
#include "knapsack.h"
#include <bitset>
#include <iostream>

/**
 * @brief Value that indicates an invalid result
 */
constexpr unsigned INVALID_RESULT = UINT_MAX;

/**
 * @brief Set of valid algorithms
 */
const std::set<std::string> valid_algorithms = {
    "brute-force", "dp-iterative", "dp-recursive-vector", "dp-recursive-map", "greedy", "integer-linear"
};


std::vector<bool> knapsack(const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned num_pallets, const unsigned max_weight, const std::string& algorithm) {
    if (valid_algorithms.find(algorithm) == valid_algorithms.end())
        throw std::runtime_error("Unknown algorithm specified: " + algorithm + ".");

    if (algorithm == "brute-force") {
        return knapsack_bf(weights, profits, num_pallets, max_weight);
    } else if (algorithm == "dp-iterative") {
        return knapsack_dp_iterative(weights, profits, num_pallets, max_weight);
    } else if (algorithm == "dp-recursive-vector") {
        return knapsack_dp_recursive_vector(weights, profits, num_pallets, max_weight);
    } else if (algorithm == "dp-recursive-map") {
        return knapsack_dp_recursive_map(weights, profits, num_pallets, max_weight);
    } else if (algorithm == "greedy") {
        return knapsack_greedy(weights, profits, num_pallets, max_weight);
    } else if (algorithm == "integer-linear") {
        return knapsack_ilp(weights, profits, num_pallets, max_weight);
    } else {
        throw std::runtime_error("Invalid algorithm specified.");
    }
}


std::vector<bool> knapsack_bf(const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned num_pallets, const unsigned max_weight) {
    std::vector<bool> used_pallets(num_pallets, false);
    if (num_pallets > 32) {
        return used_pallets;
    }
    
    unsigned combination = 0;
    unsigned best = 0;
    unsigned best_combination = INVALID_RESULT;
    while (combination < (1 << num_pallets)) {
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
    
    std::vector<std::vector<unsigned>> dp(weights.size() + 1, std::vector<unsigned>(max_weight + 1, 0));
    std::vector<std::vector<bool>> used(weights.size() + 1, std::vector<bool>(max_weight + 1, false));

    for (int i = 1; i <= weights.size(); i++) {
        for (int j = 1; j <= max_weight; j++) {
            unsigned use = j < weights[i - 1]? 0 : dp[i - 1][j - weights[i - 1]] + profits[i - 1];
            unsigned dont_use = dp[i - 1][j];
            dp[i][j] = std::max(use, dont_use);
            used[i][j] = use > dont_use;
        }
    }

    for (int i = 0; i < weights.size(); i++)
        used_pallets[i] = false;

    int i = weights.size(), j = max_weight;
    while (i > 0 && j > 0) {
        if (used[i][j]) {
            used_pallets[i - 1] = true;
            j -= weights[i - 1];
        }
        i--;
    }
        
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

inline unsigned to_flat_idx(const unsigned i, const unsigned j, const unsigned max_weight) {
    return i * (max_weight + 1) + j;
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

    unsigned current_weight = max_weight;
    std::vector<std::pair<float,unsigned>> value_per_weight;

    for (unsigned i = 0; i < num_pallets; i++)
        value_per_weight.push_back({profits[i] / (float) weights[i], i});

    std::sort(value_per_weight.rbegin(),value_per_weight.rend());

    for (unsigned i = 0; i < num_pallets; i++) {
        if (current_weight >= weights[value_per_weight[i].second]) {
            used_pallets[value_per_weight[i].second] = true;
            current_weight -= weights[value_per_weight[i].second];
        } else
            break;
    }

    return used_pallets;
}


std::vector<bool> knapsack_ilp(const std::vector<unsigned>& weights, const std::vector<unsigned>& profits, const unsigned num_pallets, const unsigned max_weight) {
    std::vector<bool> used_pallets(num_pallets, false);
    
    operations_research::MPSolver* solver(operations_research::MPSolver::CreateSolver("CBC"));
    
    std::vector<operations_research::MPVariable *> variables(num_pallets);
    for (int i = 0; i < num_pallets; i++) 
        variables[i] = solver->MakeBoolVar("x" + std::to_string(i));
    
    operations_research::MPConstraint* weight_constraint = solver->MakeRowConstraint(0.0, max_weight);
    for (int i = 0; i < num_pallets; i++)
        weight_constraint->SetCoefficient(variables[i], weights[i]);
    
    operations_research::MPObjective* objective = solver->MutableObjective();
    for (int i = 0; i < num_pallets; i++)
        objective->SetCoefficient(variables[i], profits[i]);
    
    objective->SetMaximization();
    operations_research::MPSolver::ResultStatus result_status = solver->Solve();
    
    if (result_status == operations_research::MPSolver::OPTIMAL || result_status == operations_research::MPSolver::FEASIBLE)
        for (int i = 0; i < num_pallets; i++)
            used_pallets[i] = variables[i]->solution_value();

    return used_pallets;
}