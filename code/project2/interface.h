#ifndef INTERFACE_H
#define INTERFACE_H

#include <map>
#include <string>
#include <vector>

/**
 * @brief Prints information about a command-line-interface command
 * @param command what the user wrote in the command-line-interface
 * @param info a map of every command's information
 */
void show_help_info(const std::vector<std::string>& command, std::map<std::string, std::string>& info);

/**
 * @brief Boots the command-line-interface and handles commands
 */
void start_cli();

#endif
