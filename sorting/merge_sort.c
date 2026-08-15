#include <stdio.h>
#include <stdlib.h>

void merge(int array[], int left, int mid, int right)
{
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    int *leftArray = malloc(leftSize * sizeof(int));
    int *rightArray = malloc(rightSize * sizeof(int));

    for (int i = 0; i < leftSize; i++)
        leftArray[i] = array[left + i];

    for (int i = 0; i < rightSize; i++)
        rightArray[i] = array[mid + 1 + i];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < leftSize && j < rightSize)
    {
        if (leftArray[i] <= rightArray[j])
            array[k++] = leftArray[i++];
        else
            array[k++] = rightArray[j++];
    }

    while (i < leftSize)
        array[k++] = leftArray[i++];

    while (j < rightSize)
        array[k++] = rightArray[j++];

    free(leftArray);
    free(rightArray);
}

void mergeSort(int array[], int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSort(array, left, mid);
    mergeSort(array, mid + 1, right);
    merge(array, left, mid, right);
}

int main(void)
{
    int array[] = {38, 27, 43, 3, 9, 82, 10};
    int size = sizeof(array) / sizeof(array[0]);

    mergeSort(array, 0, size - 1);

    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);

    return 0;
}
