#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int array[], int size, int root)
{
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < size && array[left] > array[largest])
        largest = left;

    if (right < size && array[right] > array[largest])
        largest = right;

    if (largest != root)
    {
        swap(&array[root], &array[largest]);
        heapify(array, size, largest);
    }
}

void heapSort(int array[], int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(array, size, i);

    for (int i = size - 1; i > 0; i--)
    {
        swap(&array[0], &array[i]);
        heapify(array, i, 0);
    }
}

int main(void)
{
    int array[] = {12, 11, 13, 5, 6, 7};
    int size = sizeof(array) / sizeof(array[0]);

    heapSort(array, size);

    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);

    return 0;
}
