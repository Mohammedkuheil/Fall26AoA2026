import matplotlib.pyplot as plt

N = [5, 10, 50, 100]

bubble_worst = [0.307, 1.143, 28.549, 107.368]
selection_worst = [0.233, 0.598, 9.571, 40.544]
insertion_worst = [0.202, 0.664, 13.316, 51.858]
merge_worst = [1.512, 3.319, 19.994, 53.880]

plt.figure(figsize=(8.5, 5))
plt.plot(N, bubble_worst, marker='o', linewidth=2, label='Bubble Sort - O(n²)')
plt.plot(N, selection_worst, marker='s', linewidth=2, label='Selection Sort - O(n²)')
plt.plot(N, insertion_worst, marker='^', linewidth=2, label='Insertion Sort - O(n²)')
plt.plot(N, merge_worst, marker='d', linewidth=2, label='Merge Sort - O(n log n)')

plt.title('Empirical Time Complexity of Sorting Algorithms (Worst-Case)')
plt.xlabel('Input Size (N)')
plt.ylabel('Average Execution Time (microseconds µs)')
plt.xticks(N)
plt.grid(True, linestyle='--', alpha=0.6)
plt.legend()
plt.tight_layout()

plt.savefig('sorting_graph.png', dpi=300)
print("Saved sorting_graph.png successfully!")
