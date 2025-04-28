#include<iostream>
#include<vector>
#include<omp.h> // For OpenMP
using namespace std;

// Sequential Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
        }
    }
}

// Parallel Bubble Sort using OpenMP
void parallelBubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        // Parallelizing the inner loop
        #pragma omp parallel for
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
        }
    }
}

// Merge two halves of an array
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);
    int i = 0, j = 0, k = left;

    while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr[i] <= rightArr[j])
            arr[k++] = leftArr[i++];
        else
            arr[k++] = rightArr[j++];
    }

    while (i < leftArr.size())
        arr[k++] = leftArr[i++];
    while (j < rightArr.size())
        arr[k++] = rightArr[j++];
}

// Sequential Merge Sort
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid+1, right);
        merge(arr, left, mid, right);
    }
}

// Parallel Merge Sort using OpenMP
void parallelMergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        // Parallelize the two recursive calls
        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, left, mid);

            #pragma omp section
            parallelMergeSort(arr, mid+1, right);
        }
        merge(arr, left, mid, right);
    }
}

// Main Function
int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    
    vector<int> arr1(n), arr2(n);
    
    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr1[i];
        arr2[i] = arr1[i]; // Copy for second sort
    }

    // Parallel Bubble Sort
    parallelBubbleSort(arr1);
    cout << "Array after Parallel Bubble Sort:\n";
    for (int i = 0; i < n; i++) {
        cout << arr1[i] << " ";
    }
    cout << "\n";

    // Parallel Merge Sort
    parallelMergeSort(arr2, 0, n-1);
    cout << "Array after Parallel Merge Sort:\n";
    for (int i = 0; i < n; i++) {
        cout << arr2[i] << " ";
    }
    cout << "\n";

    return 0;
}
