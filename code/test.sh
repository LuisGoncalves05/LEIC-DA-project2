#!/bin/bash

# Define the valid algorithms
algorithms=("brute-force" "dp_iterative" "dp_recursive_vector" "dp_recursive_map" "greedy" "integer-linear")

# Create output directory
mkdir -p results

# Loop over each algorithm and dataset
for algo in "${algorithms[@]}"; do
    echo "Running for algorithm: $algo"
    > results/$algo.txt
    for dataset in {1..10}; do
        echo -e "Dataset $dataset" >> results/$algo.txt
        timeout 10s ./DA2425_PRJ2_G21 $algo $dataset >> results/$algo.txt
        # If it times out, add a marker
        if [ $? -eq 124 ]; then
            echo -e "Used pallets:\nTIMED OUT\nTotal weight: 0\nTotal profit: 0\nSolved in TIMED OUT ns" >> results/$algo.txt
        fi
    done
done
