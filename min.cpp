#include <iostream>
#include <vector>
#include <omp.h>
#include <limits.h> // For INT_MAX and INT_MIN

using namespace std;

// Function to compute the sum of the array using Parallel Reduction
int parallelSum(const vector<int>& arr) {
    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];
    }

    return sum;
}

// Function to compute the maximum value using Parallel Reduction
int parallelMax(const vector<int>& arr) {
    int maxVal = INT_MIN;

    #pragma omp parallel for reduction(max:maxVal)
    for (int i = 0; i < arr.size(); i++) {
        maxVal = max(maxVal, arr[i]);
    }

    return maxVal;
}

// Function to compute the minimum value using Parallel Reduction
int parallelMin(const vector<int>& arr) {
    int minVal = INT_MAX;

    #pragma omp parallel for reduction(min:minVal)
    for (int i = 0; i < arr.size(); i++) {
        minVal = min(minVal, arr[i]);
    }

    return minVal;
}

// Function to compute the average of the array using Parallel Reduction
double parallelAverage(const vector<int>& arr) {
    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];
    }

    return static_cast<double>(sum) / arr.size();
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Perform Parallel Reduction operations
    int sum = parallelSum(arr);
    int maxVal = parallelMax(arr);
    int minVal = parallelMin(arr);
    double average = parallelAverage(arr);

    // Display results
    cout << "\nResults after Parallel Reduction:\n";
    cout << "Sum: " << sum << endl;
    cout << "Max: " << maxVal << endl;
    cout << "Min: " << minVal << endl;
    cout << "Average: " << average << endl;

    return 0;
}
