#ifndef IO_H
#define IO_H

#include <string>
#include <vector>

std::pair<std::vector<unsigned>, std::vector<unsigned>> read_pallets(const std::string& input_file, const unsigned num_pallets);

std::pair<unsigned, unsigned> read_truck(const std::string& input_file);

void print_output(std::vector<bool>& used_pallets, std::vector<unsigned>& weights, std::vector<unsigned>& profits, std::string& output_path);

#endif
