#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_set>
#include <windows.h>

using namespace std;

// Binary Search for use in Exponential Search
int binarySearch(const vector<long long>& arr, int left, int right, long long target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// Exponential Search Function
int exponentialSearch(const vector<long long>& arr, long long target) {
    if (arr.empty())
        return -1;

    if (arr[0] == target)
        return 0;

    int i = 1;
    int n = arr.size();
    while (i < n && arr[i] <= target)
        i *= 2;

    return binarySearch(arr, i / 2, min(i, n - 1), target);
}

int main() {
    int n;
    long long target;
    char choice;

    cout << "Enter number of elements: ";
    cin >> n;

    if (n <= 0) {
        cout << "Number of elements must be positive.\n";
        return 1;
    }

    vector<long long> numbers;
    unordered_set<long long> uniqueNumbers;

    cout << "Do you want to enter the numbers manually? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        cout << "Enter " << n << " unique long long numbers:\n";
        while (numbers.size() < n) {
            long long num;
            cin >> num;
            if (uniqueNumbers.insert(num).second) {
                numbers.push_back(num);
            } else {
                cout << "Duplicate number. Try again.\n";
            }
        }
    } else {
        random_device rd;
        mt19937_64 gen(rd());
        uniform_int_distribution<long long> dist(1e12, 9e12); // Generate long long numbers

        cout << "\nGenerated unique random numbers:\n";
        while (numbers.size() < n) {
            long long num = dist(gen);
            if (uniqueNumbers.insert(num).second) {
                numbers.push_back(num);
                cout << num << " ";
            }
        }
        cout << endl;
    }

    sort(numbers.begin(), numbers.end());

    cout << "\nSorted numbers:\n";
    for (long long num : numbers)
        cout << num << " ";
    cout << endl;

    cout << "\nEnter an element to search: ";
    cin >> target;

    // Timing using QueryPerformanceCounter (microseconds)
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    int index = exponentialSearch(numbers, target);

    QueryPerformanceCounter(&end);
    double elapsed_us = (double)(end.QuadPart - start.QuadPart) * 1'000'000.0 / freq.QuadPart;

    if (index != -1)
        cout << "Element " << target << " found at index " << index << " (0-based index)." << endl;
    else
        cout << "Element " << target << " not found in the list." << endl;

    cout << "\nExponential search runtime: " << elapsed_us << " microseconds" << endl;

    return 0;
}
