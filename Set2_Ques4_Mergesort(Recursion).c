#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int low;
    int high;
} Range;
void merge(int arr[], int low, int mid, int high, int temp[]) {
    int i = low;
    int j = mid + 1;
    int k = low;
    while (i <= mid && j <= high) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= high) {
        temp[k++] = arr[j++];
    }
    for (int l = low; l <= high; l++) {
        arr[l] = temp[l];
    }
}
void mergeSortIterative(int arr[], int n) {
    if (n <= 1) return;
    int* temp = (int*)malloc(n * sizeof(int));
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    Range* stack = (Range*)malloc(n * sizeof(Range));
    if (stack == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(temp);
        return;
    }
    int top = -1;
    stack[++top] = (Range){0, n - 1};
    while (top >= 0) {
        Range current = stack[top--];
        int low = current.low;
        int high = current.high;
        if (low < high) {
            int mid = low + (high - low) / 2;
            stack[++top] = (Range){mid + 1, high};
            stack[++top] = (Range){low, mid};
        } else if (low == high) {
        } else {
        }
    
    for (int curr_size = 1; curr_size < n; curr_size *= 2) {
        for (int low = 0; low < n - curr_size; low += 2 * curr_size) {
            int mid = low + curr_size - 1;
            int high = (low + 2 * curr_size - 1 < n) ? (low + 2 * curr_size - 1) : (n - 1);
            merge(arr, low, mid, high, temp);
        }
    }
    free(temp);
    free(stack);
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
    printf("\n");21
    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    mergeSortIterative(arr, n);
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}