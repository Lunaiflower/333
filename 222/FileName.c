#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

// ��������
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// ѡ��������
void selectionSort(int arr[], int n) {
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        if (min_idx != i)
            swap(&arr[i], &arr[min_idx]);
    }
}

// ð��������
void bubbleSort(int arr[], int n) {
    int i, j, swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }
        // ����������ڲ�ѭ���ж�û�н������������Ѿ�������õ�
        if (!swapped)
            break;
    }
}

// ��������
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    int i;
    // ����һ������
    for (i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

// �鲢������
void merge(int arr[], int temp[], int left, int left_end, int right_end) {
    int i = left, j = left_end + 1, k = left;

    while (i <= left_end && j <= right_end) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= left_end) {
        temp[k++] = arr[i++];
    }

    while (j <= right_end) {
        temp[k++] = arr[j++];
    }

    for (i = left; i <= right_end; i++)
        arr[i] = temp[i];
}

void mergeSort(int arr[], int temp[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, temp, left, mid);
        mergeSort(arr, temp, mid + 1, right);
        merge(arr, temp, left, mid, right);
    }
}

// ����������
void quickSort(int arr[], int left, int right) {
    if (left < right) {
        int pivot = arr[left];
        int i = left + 1, j = right;

        while (i < j) {
            while (i < j && arr[i] <= pivot)
                i++;
            while (i < j && arr[j] > pivot)
                j--;
            if (i < j)
                swap(&arr[i], &arr[j]);
        }

        swap(&arr[left], &arr[j]);
        quickSort(arr, left, j - 1);
        quickSort(arr, j + 1, right);
    }
}

// ����Ƚϴ���
int countComparisons(int arr[], int n, int sortMethod) {
    int comparisons = 0;

    switch (sortMethod) {
    case 1:
        selectionSort(arr, n);
        comparisons = n - 1;
        break;
    case 2:
        bubbleSort(arr, n);
        comparisons = n - 1;
        break;
    case 3:
        heapSort(arr, n);
        comparisons = 2 * n - 2;
        break;
    case 4:
        mergeSort(arr, n, 0,arr);
        comparisons = 2 * n * log2(n);
        break;
    case 5:
        quickSort(arr, 0, n - 1);
        comparisons = n * log2(n);
        break;
    default:
        printf("Invalid sort method\n");
        exit(1);
    }

    return comparisons;
}

int main() {
    int n, sortMethod;
    int arr[100];

    printf("������������������:");
    scanf("%d", &n);

    printf("��������ʽ(1: ѡ������, 2: ð������, 3: ������, 4: ��·�鲢����, 5: ��������):");
    scanf("%d", &sortMethod);

    printf("��������������(�ÿո�ָ�):");
    scanf("%d", &arr[0]);

    for (int i = 1; i < n; i++)
        scanf("%d", &arr[i]);

    int comparisons = countComparisons(arr, n, sortMethod);

    printf("������:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n��������е�Ԫ�رȽϴ���: %d\n", comparisons);

    return 0;
}