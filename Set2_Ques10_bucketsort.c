#include <stdio.h>
#include <stdlib.h>

void insertionSort(float arr[], int n) {
    for (int i = 1; i < n; i++) {
        float key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
void bucketSort(float arr[], int n) {
    float buckets[n][n];   
    int bucketCount[n];    
    for (int i = 0; i < n; i++)
        bucketCount[i] = 0;
    for (int i = 0; i < n; i++) {
        int bi = n * arr[i];  
        buckets[bi][bucketCount[bi]++] = arr[i];
    }
    for (int i = 0; i < n; i++) {
        if (bucketCount[i] > 0)
            insertionSort(buckets[i], bucketCount[i]);
    }
    int idx = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bucketCount[i]; j++) {
            arr[idx++] = buckets[i][j];
        }
    }
}
void printArray(float arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%f ", arr[i]);
    printf("\n");
}
int main() {
    float arr[] = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Original array:\n");
    printArray(arr, n);
    bucketSort(arr, n);
    printf("Sorted array:\n");
    printArray(arr, n);
    return 0;
}
