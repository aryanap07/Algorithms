#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100
#define INF INT_MAX

typedef struct {
    int source;
    int destination;
    int weight;
} Edge;

void initialize(
    int distance[],
    int parent[],
    size_t vertices,
    size_t source
) {
    for (size_t vertex = 0; vertex < vertices; vertex++) {
        distance[vertex] = INF;
        parent[vertex] = -1;
    }

    distance[source] = 0;
}

int relax_edges(
    const Edge edges[],
    size_t edge_count,
    int distance[],
    int parent[]
) {
    int changed = 0;

    for (size_t i = 0; i < edge_count; i++) {
        int source = edges[i].source;
        int destination = edges[i].destination;
        int weight = edges[i].weight;

        if (distance[source] == INF)
            continue;

        if (weight > 0 && distance[source] > INF - weight)
            continue;

        if (weight < 0 && distance[source] < INT_MIN - weight)
            continue;

        int new_distance = distance[source] + weight;

        if (new_distance < distance[destination]) {
            distance[destination] = new_distance;
            parent[destination] = source;
            changed = 1;
        }
    }

    return changed;
}

int has_negative_cycle(
    const Edge edges[],
    size_t edge_count,
    const int distance[]
) {
    for (size_t i = 0; i < edge_count; i++) {
        int source = edges[i].source;
        int destination = edges[i].destination;
        int weight = edges[i].weight;

        if (distance[source] == INF)
            continue;

        if (weight > 0 && distance[source] > INF - weight)
            continue;

        if (weight < 0 && distance[source] < INT_MIN - weight)
            continue;

        if (distance[source] + weight < distance[destination])
            return 1;
    }

    return 0;
}

int bellman_ford(
    const Edge edges[],
    size_t edge_count,
    size_t vertices,
    size_t source,
    int distance[],
    int parent[]
) {
    initialize(distance, parent, vertices, source);

    for (size_t i = 1; i < vertices; i++) {
        if (!relax_edges(edges, edge_count, distance, parent))
            break;
    }

    return !has_negative_cycle(edges, edge_count, distance);
}

void print_path(
    const int parent[],
    const int distance[],
    size_t vertex,
    size_t vertices
) {
    if (distance[vertex] == INF) {
        printf("%zu: unreachable\n", vertex);
        return;
    }

    int path[MAX];
    size_t length = 0;

    for (int current = (int)vertex;
         current != -1 && length < vertices;
         current = parent[current]) {
        path[length++] = current;
    }

    for (size_t i = length; i > 0; i--) {
        printf("%d", path[i - 1]);

        if (i > 1)
            printf(" -> ");
    }

    printf(" | Distance: %d\n", distance[vertex]);
}

int main(void) {
    const size_t vertices = 5;
    const size_t source = 0;

    const Edge edges[] = {
        {0, 1, 6},
        {0, 2, 7},
        {1, 2, 8},
        {1, 3, 5},
        {1, 4, -4},
        {2, 3, -3},
        {2, 4, 9},
        {3, 1, -2},
        {4, 0, 2},
        {4, 3, 7}
    };

    const size_t edge_count = sizeof(edges) / sizeof(*edges);

    int distance[MAX];
    int parent[MAX];

    if (!bellman_ford(
            edges,
            edge_count,
            vertices,
            source,
            distance,
            parent
        )) {
        printf("Graph contains a negative-weight cycle.\n");
        return EXIT_FAILURE;
    }

    printf("Shortest paths from vertex %zu:\n", source);

    for (size_t vertex = 0; vertex < vertices; vertex++) {
        print_path(parent, distance, vertex, vertices);
    }

    return EXIT_SUCCESS;
}
