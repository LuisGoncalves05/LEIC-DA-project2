import os
import re
import matplotlib.pyplot as plt
import numpy as np

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

algorithms = ["brute-force", "dp-iterative", "dp-recursive-vector", "dp-recursive-map", "greedy", "integer-linear"]

num_datasets = 10

fig, axs = plt.subplots(2, 5, figsize=(20, 8), constrained_layout=True)

for dataset_index in range(num_datasets):
    ax = axs[dataset_index // 5, dataset_index % 5]
    
    times_for_dataset = []
    for algo in algorithms:
        time = algorithm_times[algo][dataset_index]
        times_for_dataset.append(time if time is not None else np.nan)
    
    valid_times = [t for t in times_for_dataset if not np.isnan(t)]
    max_time = max(valid_times) if valid_times else 1
    timeout_bar_height = max_time

    plot_heights = [t if not np.isnan(t) else timeout_bar_height for t in times_for_dataset]

    bar_colors = ['skyblue' if not np.isnan(t) else 'lightcoral' for t in times_for_dataset]
    
    bars = ax.bar(algorithms, plot_heights, color=bar_colors)
    ax.set_title(f'Dataset {dataset_index + 1}')
    ax.set_ylim(0, max([t for t in times_for_dataset if not np.isnan(t)] + [1]) * 1.2)
    ax.tick_params(axis='x', rotation=45)
    
    for bar, t in zip(bars, times_for_dataset):
        if not np.isnan(t):
            label = str(int(t))
        else:
            label = "Timeout"
        y_pos = bar.get_height()
        ax.text(bar.get_x() + bar.get_width() / 2, y_pos, label,
                ha='center', va='bottom', fontsize=8)

fig.suptitle('Solve Times per Dataset and Algorithm', fontsize=16)

plt.show()
