import os
import re
import numpy as np
import matplotlib.pyplot as plt

results_folder = 'results'
time_pattern = re.compile(r"Solved in (\d+) ns")
algorithm_times = {}

for filename in os.listdir(results_folder):
    if filename.endswith(".txt"):
        algo_name = filename.replace(".txt", "")
        times = []
        with open(os.path.join(results_folder, filename), 'r') as file:
            content = file.read()
            datasets = content.split("Dataset ")
            for i in range(1, len(datasets)):
                match = time_pattern.search(datasets[i])
                if match:
                    times.append(int(match.group(1)))
                else:
                    times.append(None)
        algorithm_times[algo_name] = times

algorithms = ["dp-iterative", "dp-recursive-vector", 
              "dp-recursive-map", "greedy", "integer-linear"]
num_datasets = 10
baseline_algo = "dp-iterative"

percentages = {algo: [] for algo in algorithms if algo != baseline_algo}

for dataset_index in range(num_datasets):
    baseline_time = algorithm_times[baseline_algo][dataset_index]
    if baseline_time is None or baseline_time == 0:
        continue
    for algo in percentages:
        algo_time = algorithm_times[algo][dataset_index]
        if algo_time is None:
            continue
        perc = (algo_time / baseline_time) * 100
        percentages[algo].append(perc)

average_percentages = {}
for algo, perc_list in percentages.items():
    if perc_list:
        average_percentages[algo] = np.mean(perc_list)
    else:
        average_percentages[algo] = None  # No valid data

plt.figure(figsize=(10,6))
bars = []
labels = []
for algo in algorithms:
    if algo == baseline_algo:
        bars.append(100)
        labels.append(algo + " (baseline)")
    else:
        avg = average_percentages.get(algo)
        bars.append(avg if avg is not None else 0)
        labels.append(algo)

bar_colors = ['skyblue' if b > 0 else 'lightcoral' for b in bars]

plt.bar(labels, bars, color=bar_colors)
plt.title("Average Solve Time per Algorithm (Relative Percentages)")
plt.xticks(rotation=45)

# Add values on top of bars
for i, val in enumerate(bars):
    label = f"{val:.1f}%" if val > 0 else "No Data"
    plt.text(i, val, label, ha='center', va='bottom')

plt.yscale('log')
plt.tight_layout()
plt.show()
