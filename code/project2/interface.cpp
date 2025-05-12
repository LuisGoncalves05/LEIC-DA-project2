
#include "interface.h"

void show_help_info(const std::vector<std::string>& command, std::map<std::string, std::string>& info) {
    if (command.size() == 1) {
        for (auto& i : info) {
            if (i.first != "quit")
                std::cout << '\'' << i.first << " <database_example_number>'\n";
            else
                std::cout << '\'' << i.first << "'\n";
        }
        std::cout << "Try 'help <command>' for more details\n";
    } else {
        if (info[command[1]].empty())
            std::cout << "Invalid command\n";
        else
            std::cout << command[1] << ": " << info[command[1]] << '\n';
    }
}

void problem_sorver(std::vector<std::string>& command) {
    auto start = std::chrono::high_resolution_clock::now();
    std::string path;
    std::string algorithm = command[0];
    std::string dataset_number = command[1];
    path = "data/example" + dataset_number + "/";

    std::string pallets_path = path + "Pallets.csv";
    std::string truck_and_pallets_path = path + "TruckAndPallets.csv";
    std::string output_path = path + "Solution.txt";

    auto [max_weight, num_pallets] = std::move(read_truck(truck_and_pallets_path));
    auto [weights, profits] = std::move(read_pallets(pallets_path, num_pallets));
    auto used_pallets = std::move(knapsack(weights, profits, num_pallets, max_weight, algorithm));

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);

    print_output(used_pallets, weights, profits, output_path);

}

std::vector<unsigned> weights;
std::vector<unsigned> profits;
unsigned num_pallets;
unsigned max_weight;
std::string algorithm;
void interface() {
    std::map<std::string, std::string> info = {
        {"brute-force", "Does the problem"},
        {"dp_iterative", "Does the problem"},
        {"dp_recursive_vector", "Does the problem"},
        {"dp_recursive_map", "Does the problem"},
        {"greedy", "Does the problem"},
        {"integer-linear", "Does the problem"},
        {"quit", "Terminates the program."}
    };

    std::cout << "'help' for list of commands\n";
    while (true) {
        std::string input;
        std::cout << "$ ";
        getline(std::cin, input);
        std::stringstream ss(input);
        std::string s;
        std::vector<std::string> command;
        while (getline(ss, s, ' '))
            command.push_back(s);
        if (command[0] == "quit") {
            std::cout << "Terminating...\n";
            return;
        }
        if (command[0] == "help")
            show_help_info(command, info);
        else if (command[0] == "brute-force" || command[0] == "integer-linear" || command[0] == "greedy" || command[0] == "dp_recursive_vector" || command[0] == "dp_recursive_map" || command[0] == "dp_iterative") {
            problem_sorver(command);
        }
        else
            std::cout << "Invalid command.\n";
    }
}