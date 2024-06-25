#include <iostream>
#include <chrono>
#include <cstdlib> 
#include <ctime>  

using namespace std;
using namespace std::chrono;


void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}


void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int minIdx = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        int temp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i] = temp;
    }
}

// Merge Sort
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


void measureSortTime(void (*sortFunc)(int[], int), int arr[], int n) {
    auto start = high_resolution_clock::now();
    sortFunc(arr, n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken: " << duration.count() << " microseconds" << endl;
}

void measureSortTime(void (*sortFunc)(int[], int, int), int arr[], int low, int high) {
    auto start = high_resolution_clock::now();
    sortFunc(arr, low, high);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken: " << duration.count() << " microseconds" << endl;
}

void fillArrayRandom(int arr[], int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
}

void fillArrayReverse(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

void fillArraySorted(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
}

int main() {
    int n;
    cin>>n;
    int arr[n];
    int arr_copy[n];

    
    fillArrayRandom(arr, n);
    copy(arr, arr + n, arr_copy);
    cout << "Bubble Sort (Random Data): ";
    measureSortTime(bubbleSort, arr_copy, n);

    fillArrayReverse(arr, n);
    copy(arr, arr + n, arr_copy);
    cout << "Bubble Sort (Reverse Data): ";
    measureSortTime(bubbleSort, arr_copy, n);

    fillArraySorted(arr, n);
    copy(arr, arr + n, arr_copy);
    cout << "Bubble Sort (Sorted Data): ";
    measureSortTime(bubbleSort, arr_copy, n);

   
    fillArrayRandom(arr, n);
    copy(arr, arr + n, arr_copy);
    cout << "Insertion Sort (Random Data): ";
    measureSortTime(insertionSort, arr_copy, n);

    fillArrayReverse(arr, n);
    copy(arr, arr + n, arr_copy);
    cout << "Insertion Sort (Reverse Data): ";
    measureSortTime(insertionSort, arr_copy, n);

    fillArraySorted(arr, n);
    copy(arr, arr + n, arr_copy);
    cout << "Insertion Sort (Sorted Data): ";
    measureSortTime(insertionSort, arr_copy, n);

   
    fillArrayRandom(arr, n);
    copy(arr, arr + n, arr_copy);
    cout << "Selection Sort (Random Data): ";
    measureSortTime(selectionSort, arr_copy, n);

    fillArrayReverse(arr, n);
    copy(arr, arr + n, arr_copy);
    cout << "Selection Sort (Reverse Data): ";
    measureSortTime(selectionSort, arr_copy, n);

    fillArraySorted(arr, n);
    copy(arr, arr + n, arr_copy);
    cout << "Selection Sort (Sorted Data): ";
    measureSortTime(selectionSort, arr_copy, n);

    
    fillArrayRandom(arr, n);
    copy(arr, arr + n, arr_copy);
    cout << "Merge Sort (Random Data): ";
    measureSortTime(mergeSort, arr_copy, 0, n-1);

    fillArrayReverse(arr, n);
    copy(arr, arr + n, arr_copy);
    cout << "Merge Sort (Reverse Data): ";
    measureSortTime(mergeSort, arr_copy, 0, n-1);

    fillArraySorted(arr, n);
    copy(arr, arr + n, arr_copy);
    cout << "Merge Sort (Sorted Data): ";
    measureSortTime(mergeSort, arr_copy, 0, n-1);


    fillArrayRandom(arr, n);
    copy(arr, arr + n, arr_copy);
    cout << "Quick Sort (Random Data): ";
    measureSortTime(quickSort, arr_copy, 0, n-1);

    fillArrayReverse(arr, n);
    copy(arr, arr + n, arr_copy);
    cout << "Quick Sort (Reverse Data): ";
    measureSortTime(quickSort, arr_copy, 0, n-1);

    fillArraySorted(arr, n);
    copy(arr, arr + n, arr_copy);
    cout << "Quick Sort (Sorted Data): ";
    measureSortTime(quickSort, arr_copy, 0, n-1);

    return 0;
}
