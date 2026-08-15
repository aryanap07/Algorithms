#include <stdio.h>

int binary_search(const int array[], int size, int target)
{
    int left = 0;
    int right = size - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (array[mid] == target)
            return mid;

        if (array[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

int main(void)
{
    int array[] = {10, 20, 30, 40, 50, 60, 70};
    int size = sizeof(array) / sizeof(array[0]);
    int target = 40;

    int index = binary_search(array, size, target);

    printf("%d\n", index);

    return 0;
}
