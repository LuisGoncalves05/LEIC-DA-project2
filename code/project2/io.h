#ifndef IO_H
#define IO_H

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

/**
 * @brief Reads and parses the truck and pallets information from a CSV file
 * @param input_file path to the CSV file
 * @param max_weights maximum weight of the truck
 * @param num_pallets number of pallets
 */
void read_truck(const std::string& input_file, unsigned &max_weights, unsigned &num_pallets);

/**
 * @brief Reads and parses the pallets weight and profit information from a CSV file
 * @param input_file path to the CSV file
 * @param weights weights of the pallets
 * @param profits profits of the pallets
 */
void read_pallets(const std::string& input_file, std::vector<unsigned> &weights, std::vector<unsigned> &profits);

/**
 * @brief Parses and writes to a CSV file the output of the knapsack problem
 * @param used_pallets which pallets are part of the solution
 * @param weights weights of the pallets
 * @param profits profits of the pallets
 * @param output_path path to the output file
 */
void write_output(std::vector<bool>& used_pallets, std::vector<unsigned>& weights, std::vector<unsigned>& profits, std::string& output_path);

/**
 * @brief Parses and prints the output of the knapsack problem
 * @param used_pallets which pallets are part of the solution
 * @param weights weights of the pallets
 * @param profits profits of the pallets
 */
void print_output(std::vector<bool>& used_pallets, std::vector<unsigned>& weights, std::vector<unsigned>& profits);

#endif
