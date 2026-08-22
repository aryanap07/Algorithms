#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

void print_matrix(const int graph[][5], size_t vertices) {
    for (size_t i = 0; i < vertices; i++) {
        for (size_t j = 0; j < vertices; j++) {
            if (graph[i][j] == INF)
                printf("%4s", "INF");
            else
                printf("%4d", graph[i][j]);
        }

        printf("\n");
    }
}

void floyd_warshall(
    const int graph[][5],
    int distance[][5],
    size_t vertices
) {
    for (size_t i = 0; i < vertices; i++) {
        for (size_t j = 0; j < vertices; j++)
            distance[i][j] = graph[i][j];
    }

    for (size_t k = 0; k < vertices; k++) {
        for (size_t i = 0; i < vertices; i++) {
            if (distance[i][k] == INF)
                continue;

            for (size_t j = 0; j < vertices; j++) {
                if (distance[k][j] == INF)
                    continue;

                int through_k = distance[i][k] + distance[k][j];

                if (through_k < distance[i][j])
                    distance[i][j] = through_k;
            }
        }
    }
}

int has_negative_cycle(const int distance[][5], size_t vertices) {
    for (size_t i = 0; i < vertices; i++) {
        if (distance[i][i] < 0)
            return 1;
    }

    return 0;
}

int main(void) {
    const size_t vertices = 5;

    const int graph[5][5] = {
        {0, 3, 8, INF, -4},
        {INF, 0, INF, 1, 7},
        {INF, 4, 0, INF, INF},
        {2, INF, -5, 0, INF},
        {INF, INF, INF, 6, 0}
    };

    int distance[5][5];

    floyd_warshall(graph, distance, vertices);

    if (has_negative_cycle(distance, vertices)) {
        printf("Graph contains a negative-weight cycle.\n");
        return EXIT_FAILURE;
    }

    printf("All-Pairs Shortest Paths:\n");
    print_matrix(distance, vertices);

    return EXIT_SUCCESS;
}
