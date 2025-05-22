#ifndef INTERFACE_H
#define INTERFACE_H

#include <vector>
#include <map>
#include <string>

/**
 * @brief Prints information about a command-line-interface command
 * @param command command-line-interface input
 * @param info all commands' information
 */
void show_help_info(const std::vector<std::string>& command, const std::map<std::string, std::string>& info);

/**
 * @brief Calls a chosen algorithm to solve the knapsack problem and prints output
 * @param command command-line-interface input
 */
 void problem_solver(const std::vector<std::string>& command);

/**
 * @brief Boots the command-line-interface and handles commands
 */
void interface();


#endif
