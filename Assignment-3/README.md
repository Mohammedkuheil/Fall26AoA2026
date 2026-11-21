# Assignment 3 — Empirical Analysis of Sorting Algorithms

Empirical time and space comparison of **Selection Sort**, **Bubble Sort**, **Quick Sort**, and **Merge Sort** across array sizes **5** and **100** in both **Sorted** and **Reverse Sorted** orders (16 cases total, averaged over 3 runs per case)[cite: 8, 9].

## Files in This Folder
- `assignment3_sorting.cpp` — C++ implementation of all four sorting algorithms from scratch, measuring execution time (`clock()`), average runtime across 3 runs, auxiliary space behavior, and comparison/swap counts[cite: 8, 9].

## How to Run
```bash
g++ assignment3_sorting.cpp -o assignment3_sorting
./assignment3_sorting
