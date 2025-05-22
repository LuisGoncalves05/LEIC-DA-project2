import os
import re
import matplotlib.pyplot as plt
import numpy as np

results_folder = 'results'

time_pattern = re.compile(r"Solved in (\d+) ns")
profit_pattern = re.compile(r"Total profit: (\d+)")

algorithms = ["dp-iterative", "greedy"]
num_datasets = 10

algorithm_times = {algo: [] for algo in algorithms}
algorithm_profits = {algo: [] for algo in algorithms}

# Load data
for algo in algorithms:
    filepath = os.path.join(results_folder, f"{algo}.txt")
    with open(filepath, 'r') as file:
        content = file.read()
        datasets = content.split("Dataset ")
        for i in range(1, len(datasets)):
            time_match = time_pattern.search(datasets[i])
            profit_match = profit_pattern.search(datasets[i])
            time = int(time_match.group(1)) if time_match else None
            profit = int(profit_match.group(1)) if profit_match else None
            algorithm_times[algo].append(time)
            algorithm_profits[algo].append(profit)

# Calculate metrics for all datasets
time_speedups = []
profit_diff_pcts = []

for i in range(num_datasets):
    dp_time = algorithm_times["dp-iterative"][i]
    greedy_time = algorithm_times["greedy"][i]
    dp_profit = algorithm_profits["dp-iterative"][i]
    greedy_profit = algorithm_profits["greedy"][i]

    if dp_time is None or greedy_time is None or greedy_time == 0:
        time_speedup = 0
    else:
        time_speedup = dp_time / greedy_time

    if dp_profit is None or greedy_profit is None or dp_profit == 0:
        profit_diff_pct = 0
    else:
        profit_diff_pct = ((dp_profit - greedy_profit) / dp_profit) * 100

    time_speedups.append(time_speedup)
    profit_diff_pcts.append(profit_diff_pct)

# Plotting all datasets in one figure
fig, ax_left = plt.subplots(figsize=(14, 6))

x = np.arange(num_datasets)
width = 0.4

# Bars for time speedup (left y-axis)
bars_left = ax_left.bar(x - width/2, time_speedups, width, color='steelblue', label='Time Speedup (times faster)')

ax_left.tick_params(axis='y', labelcolor='steelblue')
ax_left.set_ylim(0, max(time_speedups) * 1.5 if max(time_speedups) > 1 else 2)

# Right y-axis for profit difference %
ax_right = ax_left.twinx()
bars_right = ax_right.bar(x + width/2, profit_diff_pcts, width, color='tomato', label='Profit Difference (%)')

ax_right.tick_params(axis='y', labelcolor='tomato')

# Set x-axis labels and title
ax_left.set_xticks(x)
ax_left.set_xticklabels([f'Dataset {i+1}' for i in range(num_datasets)], rotation=45, ha='right')

ax_left.set_title('Time Speedup and Profit Difference % per Dataset')

# Add value labels on bars
for bar in bars_left:
    height = bar.get_height()
    ax_left.text(bar.get_x() + bar.get_width()/2, height, f'{height:.2f}', ha='center', va='bottom', fontsize=8, color='steelblue')

for bar in bars_right:
    height = bar.get_height()
    ax_right.text(bar.get_x() + bar.get_width()/2, height, f'{height:.2f}%', ha='center', va='bottom', fontsize=8, color='tomato')

# Combine legends from both axes
handles_left, labels_left = ax_left.get_legend_handles_labels()
handles_right, labels_right = ax_right.get_legend_handles_labels()
ax_left.legend(handles_left + handles_right, labels_left + labels_right, loc='upper left')


plt.tight_layout()
plt.show()
