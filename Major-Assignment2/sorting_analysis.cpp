#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include <algorithm>
#include <iomanip>

using namespace std;
using namespace std::chrono;

// 1. Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 2. Selection Sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[min_idx], arr[i]);
    }
}

// 3. Insertion Sort
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 4. Merge Sort
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSortHelper(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSortHelper(arr, left, mid);
    mergeSortHelper(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void mergeSort(vector<int>& arr) {
    mergeSortHelper(arr, 0, arr.size() - 1);
}

// (microseconds)
template <typename Func>
double measureAverageTime(Func sortFunc, const vector<int>& baseArr, int runs = 10) {
    double totalMicroseconds = 0.0;
    for (int r = 0; r < runs; r++) {
        vector<int> arrCopy = baseArr;
        auto start = high_resolution_clock::now();
        sortFunc(arrCopy);
        auto stop = high_resolution_clock::now();
        
        duration<double, micro> elapsed = stop - start;
        totalMicroseconds += elapsed.count();
    }
    return totalMicroseconds / runs;
}

int main() {
    vector<int> sizes = {5, 10, 50, 100};
    int runs = 10;

    cout << fixed << setprecision(3);

    for (bool worstCase : {false, true}) {
        cout << "\n=== " << (worstCase ? "WORST-CASE INPUT (Descending: N to 1)" : "GIVEN INPUT (Ascending: 1 to N)") << " ===\n";
        cout << "N\tBubble(us)\tSelection(us)\tInsertion(us)\tMerge(us)\n";

        for (int n : sizes) {
            vector<int> arr(n);
            if (!worstCase) {
                iota(arr.begin(), arr.end(), 1);
            } else {
                for (int i = 0; i < n; i++) arr[i] = n - i;
            }

            double tBubble = measureAverageTime(bubbleSort, arr, runs);
            double tSelection = measureAverageTime(selectionSort, arr, runs);
            double tInsertion = measureAverageTime(insertionSort, arr, runs);
            double tMerge = measureAverageTime(mergeSort, arr, runs);

            cout << n << "\t" << tBubble << "\t\t" << tSelection << "\t\t" 
                 << tInsertion << "\t\t" << tMerge << "\n";
        }
    }
    return 0;
}
