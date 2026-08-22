#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
 
#define MAX 100 
#define INF INT_MAX 
 
int select_min_vertex(const int distance[], const int visited[], size_t vertices) { 
    int min_distance = INF; 
    int min_vertex = -1; 
 
    for (size_t vertex = 0; vertex < vertices; vertex++) { 
        if (!visited[vertex] && distance[vertex] < min_distance) { 
            min_distance = distance[vertex]; 
            min_vertex = (int)vertex; 
        } 
    } 
 
    return min_vertex; 
} 
 
void dijkstra( 
    const int graph[MAX][MAX], 
    int distance[], 
    int parent[], 
    size_t vertices, 
    size_t source 
) { 
    int visited[MAX] = {0}; 
 
    for (size_t vertex = 0; vertex < vertices; vertex++) { 
        distance[vertex] = INF; 
        parent[vertex] = -1; 
    } 
 
    distance[source] = 0; 
 
    for (size_t count = 0; count < vertices; count++) { 
        int current = select_min_vertex(distance, visited, vertices); 
 
        if (current == -1) 
            break; 
 
        visited[current] = 1; 
 
        for (size_t neighbor = 0; neighbor < vertices; neighbor++) { 
            if (visited[neighbor] || graph[current][neighbor] == INF) 
                continue; 
 
            if (distance[current] > INF - graph[current][neighbor]) 
                continue; 
 
            int new_distance = 
                distance[current] + graph[current][neighbor]; 
 
            if (new_distance < distance[neighbor]) { 
                distance[neighbor] = new_distance; 
                parent[neighbor] = current; 
            } 
        } 
    } 
} 
 
void print_paths( 
    const int distance[], 
    const int parent[], 
    size_t vertices, 
    size_t source 
) { 
    for (size_t vertex = 0; vertex < vertices; vertex++) { 
        printf("%zu: ", vertex); 
 
        if (distance[vertex] == INF) { 
            printf("unreachable\n"); 
            continue; 
        } 
 
        int path[MAX]; 
        size_t length = 0; 
 
        for (int current = (int)vertex; 
             current != -1; 
             current = parent[current]) 
            path[length++] = current; 
 
        for (size_t i = length; i > 0; i--) { 
            printf("%d", path[i - 1]); 
 
            if (i > 1) 
                printf(" -> "); 
        } 
 
        printf(" | Distance: %d\n", distance[vertex]); 
    } 
 
    (void)source; 
} 
 
int main(void) { 
    const size_t vertices = 6; 
    const size_t source = 0; 
 
    const int graph[MAX][MAX] = { 
        {0, 4, 2, INF, INF, INF}, 
        {4, 0, 1, 5, INF, INF}, 
        {2, 1, 0, 8, 10, INF}, 
        {INF, 5, 8, 0, 2, 6}, 
        {INF, INF, 10, 2, 0, 3}, 
        {INF, INF, INF, 6, 3, 0} 
    }; 
 
    int distance[MAX]; 
    int parent[MAX]; 
 
    dijkstra(graph, distance, parent, vertices, source); 
 
    printf("Shortest paths from vertex %zu:\n", source); 
    print_paths(distance, parent, vertices, source); 
 
    return EXIT_SUCCESS; 
}
