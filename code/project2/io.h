#ifndef IO_H
#define IO_H

#include <string>
#include <vector>

std::pair<std::vector<int>, std::vector<int>> read_pallets(const std::string& input_file);

std::pair<int, int> read_truck(const std::string& input_file);

void print_output(std::vector<int>& result_weights, std::vector<int>& result_profits, std::string& output_path);

#endif
