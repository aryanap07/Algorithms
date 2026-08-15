#include <stdio.h>

int linear_search(const int arr[], int size, int target)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == target)
            return i;
    }

    return -1;
}

int main(void)
{
    int arr[] = {10, 25, 30, 45, 50};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 45;

    int index = linear_search(arr, size, target);

    if (index != -1)
        printf("Element found at index %d\n", index);
    else
        printf("Element not found\n");

    return 0;
}
