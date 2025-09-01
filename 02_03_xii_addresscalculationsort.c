#include <stdio.h>
#include <stdlib.h>

void insertionSort(int arr[], int n) {
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
void addressCalculationSort(int arr[], int n) {
    int min = arr[0], max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
    int bucketCount = n;
    int range = max - min + 1;
    int *buckets[n];
    int bucketSizes[n];
    for (int i = 0; i < n; i++) {
        buckets[i] = (int *)malloc(n * sizeof(int));
        bucketSizes[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        int index = (arr[i] - min) * bucketCount / range; 
        if (index >= n) index = n - 1;
        buckets[index][bucketSizes[index]++] = arr[i];
    }
    for (int i = 0; i < n; i++) {
        if (bucketSizes[i] > 1)
            insertionSort(buckets[i], bucketSizes[i]);
    }
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bucketSizes[i]; j++) {
            arr[k++] = buckets[i][j];
        }
        free(buckets[i]);
    }
}
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
int main() {
    int arr[] = {29, 25, 3, 49, 9, 37, 21, 43};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Original array:\n");
    printArray(arr, n);
    addressCalculationSort(arr, n);
    printf("Sorted array:\n");
    printArray(arr, n);
    return 0;
}
