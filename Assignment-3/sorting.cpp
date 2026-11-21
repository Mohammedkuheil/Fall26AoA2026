#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Metrics {
    long long comparisons = 0;
    long long swaps = 0;
};

// 1. Selection Sort (In-place, O(1) auxiliary space)
void selectionSort(vector<int>& arr, Metrics& m) {
    int n = static_cast<int>(arr.size());
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            m.comparisons++;
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swap(arr[i], arr[minIdx]);
            m.swaps++;
        }
    }
}

// 2. Bubble Sort (In-place, O(1) auxiliary space)
void bubbleSort(vector<int>& arr, Metrics& m) {
    int n = static_cast<int>(arr.size());
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            m.comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                m.swaps++;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

// 3. Quick Sort using Lomuto partition (In-place recursion stack O(log n) avg, O(n) worst)
int partitionArray(vector<int>& arr, int low, int high, Metrics& m) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        m.comparisons++;
        if (arr[j] <= pivot) {
            ++i;
            if (i != j) {
                swap(arr[i], arr[j]);
                m.swaps++;
            }
        }
    }
    if (i + 1 != high) {
        swap(arr[i + 1], arr[high]);
        m.swaps++;
    }
    return i + 1;
}

void quickSortHelper(vector<int>& arr, int low, int high, Metrics& m) {
    if (low < high) {
        int pi = partitionArray(arr, low, high, m);
        quickSortHelper(arr, low, pi - 1, m);
        quickSortHelper(arr, pi + 1, high, m);
    }
}

void quickSort(vector<int>& arr, Metrics& m) {
    if (!arr.empty()) {
        quickSortHelper(arr, 0, static_cast<int>(arr.size()) - 1, m);
    }
}

// 4. Merge Sort (Requires extra temporary arrays: O(n) auxiliary space)
void mergeSubarrays(vector<int>& arr, int left, int mid, int right, Metrics& m) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> leftArr(n1);
    vector<int> rightArr(n2);

    for (int i = 0; i < n1; ++i) leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; ++j) rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        m.comparisons++;
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
            m.swaps++;
        }
    }
    while (i < n1) {
        arr[k++] = leftArr[i++];
    }
    while (j < n2) {
        arr[k++] = rightArr[j++];
    }
}

void mergeSortHelper(vector<int>& arr, int left, int right, Metrics& m) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(arr, left, mid, m);
        mergeSortHelper(arr, mid + 1, right, m);
        mergeSubarrays(arr, left, mid, right, m);
    }
}

void mergeSort(vector<int>& arr, Metrics& m) {
    if (!arr.empty()) {
        mergeSortHelper(arr, 0, static_cast<int>(arr.size()) - 1, m);
    }
}

vector<int> makeArray(int n, bool reverseOrder) {
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = reverseOrder ? (n - i) : (i + 1);
    }
    return arr;
}

template <typename SortFn>
void benchmarkAlgorithm(const string& algoName, const string& auxSpaceDesc, SortFn sortFunc) {
    struct CaseSpec {
        int size;
        bool reversed;
        string label;
    };

    vector<CaseSpec> cases = {
        {5, false, "N=5 Sorted"},
        {5, true,  "N=5 Reverse"},
        {100, false, "N=100 Sorted"},
        {100, true,  "N=100 Reverse"}
    };

    cout << "\n============================================================\n";
    cout << "Algorithm: " << algoName << " | Auxiliary Space: " << auxSpaceDesc << "\n";
    cout << "Case           | Run1(ms) | Run2(ms) | Run3(ms) | Avg(ms)  | Comps | Swaps\n";
    cout << "----------------------------------------------------------------------------\n";

    for (const auto& c : cases) {
        vector<int> base = makeArray(c.size, c.reversed);
        double timesMs[3] = {0.0, 0.0, 0.0};
        Metrics lastMetrics;

        for (int r = 0; r < 3; ++r) {
            vector<int> copyArr = base;
            Metrics m;
            clock_t start = clock();
            sortFunc(copyArr, m);
            clock_t end = clock();

            timesMs[r] = (static_cast<double>(end - start) / CLOCKS_PER_SEC) * 1000.0;
            lastMetrics = m;
        }

        double avgMs = (timesMs[0] + timesMs[1] + timesMs[2]) / 3.0;
        cout << left << setw(15) << c.label << "| "
             << fixed << setprecision(5)
             << setw(9) << timesMs[0] << "| "
             << setw(9) << timesMs[1] << "| "
             << setw(9) << timesMs[2] << "| "
             << setw(9) << avgMs << "| "
             << setw(6) << lastMetrics.comparisons << "| "
             << lastMetrics.swaps << "\n";
    }
}

int main() {
    benchmarkAlgorithm("Selection Sort", "O(1) auxiliary (in-place)", selectionSort);
    benchmarkAlgorithm("Bubble Sort", "O(1) auxiliary (in-place)", bubbleSort);
    benchmarkAlgorithm("Quick Sort", "O(log n) avg / O(n) worst stack", quickSort);
    benchmarkAlgorithm("Merge Sort", "O(n) auxiliary (temp arrays)", mergeSort);
    return 0;
}
