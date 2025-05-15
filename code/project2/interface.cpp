#include <chrono>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "io.h"
#include "interface.h"
#include "knapsack.h"

void show_help_info(const std::vector<std::string>& command, const std::map<std::string, std::string>& info) {
    if (command.size() == 1) {
        for (const auto& i : info) {
            if (i.first != "quit")
                std::cout << '\'' << i.first << " <database_example_number>'\n";
            else
                std::cout << '\'' << i.first << "'\n";
        }
        std::cout << "Try 'help <command>' for more details\n";
    } else {
        auto it = info.find(command[1]);
        if (it == info.end())
            std::cout << "Invalid command\n";
        else
            std::cout << command[1] << ": " << it->second << '\n';
    }
}

void problem_solver(const std::vector<std::string>& command) {
    if (command.size() < 2) {
        std::cout << "Usage: <algorithm> <example_number>\n";
        return;
    }

    std::string path = "data/example" + command[1] + "/";
    std::string pallets_path = path + "Pallets.csv";
    std::string truck_and_pallets_path = path + "TruckAndPallets.csv";

    unsigned max_weight;
    unsigned num_pallets;

    read_truck(truck_and_pallets_path, max_weight, num_pallets);

    std::vector<unsigned> weights(num_pallets);
    std::vector<unsigned> profits(num_pallets);
    read_pallets(pallets_path, weights, profits);

    auto start = std::chrono::high_resolution_clock::now();

    auto used_pallets = knapsack(weights, profits, num_pallets, max_weight, command[0]);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    print_output(used_pallets, weights, profits);
    std::cout << "Solved in " << duration.count() << " ms\n";
}

void interface() {
    std::map<std::string, std::string> info = {
        {"brute-force", "Solves the problem using brute force."},
        {"dp_iterative", "Solves the problem using iterative dynamic programming."},
        {"dp_recursive_vector", "Solves the problem using top-down dynamic programming with vector memoization."},
        {"dp_recursive_map", "Solves the problem using top-down dynamic programming with map memoization."},
        {"greedy", "Solves the problem using a greedy approach."},
        {"integer-linear", "Solves the problem using integer linear programming."},
        {"quit", "Terminates the program."}
    };

    std::cout << "'help' for list of commands\n";
    while (true) {
        std::string input;
        std::cout << "$ ";
        std::getline(std::cin, input);

        std::stringstream ss(input);
        std::string s;
        std::vector<std::string> command;

        while (ss >> s)
            command.push_back(s);

        if (command.empty())
            continue;

        if (command[0] == "quit") {
            std::cout << "Terminating...\n";
            break;
        } else if (command[0] == "help")
            show_help_info(command, info);
        else if (info.count(command[0]))
            problem_solver(command);
        else
            std::cout << "Invalid command.\n";
    }
}
