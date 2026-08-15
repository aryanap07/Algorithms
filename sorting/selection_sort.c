#include <stdio.h>

void selection_sort(int array[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int min_index = i;

        for (int j = i + 1; j < size; j++)
        {
            if (array[j] < array[min_index])
                min_index = j;
        }

        if (min_index != i)
        {
            int temp = array[i];
            array[i] = array[min_index];
            array[min_index] = temp;
        }
    }
}

int main(void)
{
    int array[] = {64, 25, 12, 22, 11};
    int size = sizeof(array) / sizeof(array[0]);

    selection_sort(array, size);

    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);

    return 0;
}
