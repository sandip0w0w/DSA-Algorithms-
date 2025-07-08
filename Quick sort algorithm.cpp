#include <iostream>
#include <vector>
#include <cstdlib>     // For rand() and srand()
#include <ctime>       // For time()
#include <windows.h>   // For QueryPerformanceCounter

using namespace std;

// Partition function for Quick Sort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Choose last element as pivot
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick Sort recursive function
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int N, choice;

    cout << "Enter number of elements: ";
    cin >> N;

    vector<int> arr(N);

    cout << "Choose input type:\n";
    cout << "1. Random Input (4-digit numbers)\n";
    cout << "2. Manual Input\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    if (choice == 1) {
        srand(time(0));
        cout << "\nOriginal array (Random 4-digit numbers):\n";
        for (int i = 0; i < N; i++) {
            arr[i] = rand() % 9000 + 1000;  // Range [1000, 9999]
            cout << arr[i] << " ";
        }
    } else if (choice == 2) {
        cout << "\nEnter " << N << " integers:\n";
        for (int i = 0; i < N; i++) {
            cout << "Element " << i + 1 << ": ";
            cin >> arr[i];
        }

        cout << "\nOriginal array (Manual):\n";
        for (int val : arr)
            cout << val << " ";
    } else {
        cout << "Invalid choice. Exiting.\n";
        return 1;
    }

    // Measure runtime using QueryPerformanceCounter
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    quickSort(arr, 0, N - 1);

    QueryPerformanceCounter(&end);
    double elapsed_ms = (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;

    // Output sorted array
    cout << "\n\nSorted array in ascending order:\n";
    for (int val : arr)
        cout << val << " ";

    cout << "\n\nTime taken by Quick Sort: " << elapsed_ms << " milliseconds\n";

    return 0;
}
