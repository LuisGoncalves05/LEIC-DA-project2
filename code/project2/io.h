#ifndef IO_H
#define IO_H

#include <string>
#include <vector>

void read_truck(const std::string& input_file, unsigned &max_weights, unsigned &num_pallets);
void read_pallets(const std::string& input_file, std::vector<unsigned> &weights, std::vector<unsigned> &profits);

void print_output(std::vector<bool>& used_pallets, std::vector<unsigned>& weights, std::vector<unsigned>& profits, std::string& output_path);

#endif
