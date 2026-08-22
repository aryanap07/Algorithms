#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    double weight;
    double value;
    double ratio;
} Item;

int compare_items(const void *a, const void *b) {
    const Item *first = a;
    const Item *second = b;

    if (first->ratio < second->ratio)
        return 1;

    if (first->ratio > second->ratio)
        return -1;

    return 0;
}

double fractional_knapsack(
    Item items[],
    size_t count,
    double capacity,
    double selected[]
) {
    qsort(items, count, sizeof(*items), compare_items);

    double total_value = 0.0;
    double remaining = capacity;

    for (size_t i = 0; i < count && remaining > 0.0; i++) {
        if (items[i].weight <= remaining) {
            selected[i] = 1.0;
            remaining -= items[i].weight;
            total_value += items[i].value;
        } else {
            selected[i] = remaining / items[i].weight;
            total_value += items[i].value * selected[i];
            remaining = 0.0;
        }
    }

    return total_value;
}

void display_solution(
    const Item items[],
    const double selected[],
    size_t count,
    double total_value
) {
    printf("Selected items:\n");

    for (size_t i = 0; i < count; i++) {
        if (selected[i] > 0.0) {
            printf(
                "Item %d: %.2f%%\n",
                items[i].id,
                selected[i] * 100.0
            );
        }
    }

    printf("Maximum value: %.2f\n", total_value);
}

int main(void) {
    Item items[] = {
        {1, 10.0, 60.0, 0.0},
        {2, 20.0, 100.0, 0.0},
        {3, 30.0, 120.0, 0.0}
    };

    size_t count = sizeof(items) / sizeof(*items);
    double capacity = 50.0;

    for (size_t i = 0; i < count; i++)
        items[i].ratio = items[i].value / items[i].weight;

    double *selected = calloc(count, sizeof(*selected));

    if (selected == NULL) {
        perror("calloc");
        return EXIT_FAILURE;
    }

    double total_value = fractional_knapsack(
        items,
        count,
        capacity,
        selected
    );

    display_solution(items, selected, count, total_value);

    free(selected);

    return EXIT_SUCCESS;
}
