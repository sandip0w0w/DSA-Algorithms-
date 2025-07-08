#include <iostream>
#include <vector>
#include <windows.h>   // For QueryPerformanceCounter
#include <cstdlib>     // For rand() and srand()
#include <ctime>       // For time()

using namespace std;

// Merge two halves of the vector
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Merge Sort function
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    int N, choice;

    cout << "Enter the number of elements: ";
    cin >> N;

    vector<int> arr(N);

    cout << "Choose input type:\n";
    cout << "1. Random Input\n";
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
        cout << "\nEnter " << N << " elements:\n";
        for (int i = 0; i < N; i++) {
            cout << "Element " << i + 1 << ": ";
            cin >> arr[i];
        }
        cout << "\nOriginal array (Manual):\n";
        for (int i = 0; i < N; i++) {
            cout << arr[i] << " ";
        }
    } else {
        cout << "Invalid choice. Exiting.\n";
        return 1;
    }

    // Start timing using QueryPerformanceCounter
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    mergeSort(arr, 0, N - 1);

    QueryPerformanceCounter(&end);
    double elapsed_ms = (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;

    cout << "\n\nSorted array using Merge Sort:\n";
    for (int num : arr)
        cout << num << " ";

    cout << "\n\nTime taken by Merge Sort: " << elapsed_ms << " milliseconds\n";

    return 0;
}
