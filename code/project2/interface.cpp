#include <fstream>
#include <sstream>
#include <iostream>

#include "interface.h"
#include "io.h"

// Nothing here quite done, just left this stub because it may be useful for future souls doing this
void start_cli() {
    std::map<std::string, std::string> info = {
        {"batch", "Reads the file in <input_file_path> and processes it to the file <output_file_path>. If no paths are provided, the default input and output files are used."},
        {"plan_route", "Starts the Route Planning Program."},
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
        } else if (command[0] == "help") {
            show_help_info(command, info);
        } else if (command[0] == "batch") {
            
        } else if (command[0] == "plan_route") {
            
        } else
            std::cout << "Invalid command.\n";
    }
}


// Nothing here quite done, just left this stub because it may be useful for future souls doing this
void show_help_info(const std::vector<std::string>& command, std::map<std::string, std::string>& info) {
    if (command.size() == 1) {
        for (auto& i : info) {
            if (i.first == "batch")
                std::cout << '\'' << i.first << " <input_file_path> <output_file_path>'\n";
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