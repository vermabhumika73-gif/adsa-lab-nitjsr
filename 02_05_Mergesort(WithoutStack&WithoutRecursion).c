#include <stdio.h>
#include <stdlib.h> 

void merge(int arr[], int temp[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    for (i = 0; i < n1; i++)
        temp[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        temp[n1 + j] = arr[mid + 1 + j];
    i = 0; 
    j = n1; 
    k = left;
    while (i < n1 && j < (n1 + n2)) {
        if (temp[i] <= temp[j]) {
            arr[k] = temp[i];
            i++;
        } else {
            arr[k] = temp[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = temp[i];
        i++;
        k++;
    }
    while (j < (n1 + n2)) {
        arr[k] = temp[j];
        j++;
        k++;
    }
}
void iterativeMergeSort(int arr[], int n) {
    int curr_size; 
    int left_start; 
    int *temp = (int *)malloc(sizeof(int) * n);
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) 
        for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
        
            int mid = left_start + curr_size - 1;
            int right_end = (left_start + 2 * curr_size - 1 < n - 1) ? (left_start + 2 * curr_size - 1) : (n - 1);
            if (mid < n - 1) {
                merge(arr, temp, left_start, mid, right_end);
            }
        }
    }
    free(temp);
}
void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
int main() {
    int n;
    printf("Enter the size of array: ");
    scanf("%d",&n);
    int arr[n];
    printf("Enter the elements of array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d ",&arr[i]);
    }
    printf("\n");
    printf("Given array is \n");
    printArray(arr, n);
    iterativeMergeSort(arr, n);
    printf("Sorted array is \n");
    printArray(arr, n);
    return 0;
}
