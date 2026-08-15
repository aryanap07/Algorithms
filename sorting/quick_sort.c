#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int array[], int low, int high)
{
    int pivot = array[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (array[j] <= pivot)
        {
            i++;
            swap(&array[i], &array[j]);
        }
    }

    swap(&array[i + 1], &array[high]);
    return i + 1;
}

void quickSort(int array[], int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partition(array, low, high);

        quickSort(array, low, pivotIndex - 1);
        quickSort(array, pivotIndex + 1, high);
    }
}

int main(void)
{
    int array[] = {10, 7, 8, 9, 1, 5};
    int size = sizeof(array) / sizeof(array[0]);

    quickSort(array, 0, size - 1);

    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);

    return 0;
}
