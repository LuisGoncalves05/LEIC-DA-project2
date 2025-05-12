#ifndef INTERFACE_H
#define INTERFACE_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include "io.h"
#include "knapsack.h"

/**
 * @brief Prints information about a command-line-interface command
 * @param command what the user wrote in the command-line-interface
 * @param info a map of every command's information
 */
void show_help_info(const std::vector<std::string>& command, std::map<std::string, std::string>& info);

/**
 * @brief Boots the command-line-interface and handles commands
 */
void interface();

#endif
