#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *board;
    int *columns;
    int *diagonal1;
    int *diagonal2;
    size_t size;
    size_t solutions;
} NQueens;

NQueens *create_solver(size_t size) {
    NQueens *solver = malloc(sizeof(*solver));

    if (solver == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    solver->size = size;
    solver->solutions = 0;

    solver->board = calloc(size, sizeof(*solver->board));
    solver->columns = calloc(size, sizeof(*solver->columns));
    solver->diagonal1 = calloc(2 * size - 1, sizeof(*solver->diagonal1));
    solver->diagonal2 = calloc(2 * size - 1, sizeof(*solver->diagonal2));

    if (solver->board == NULL ||
        solver->columns == NULL ||
        solver->diagonal1 == NULL ||
        solver->diagonal2 == NULL) {
        perror("calloc");
        free(solver->board);
        free(solver->columns);
        free(solver->diagonal1);
        free(solver->diagonal2);
        free(solver);
        exit(EXIT_FAILURE);
    }

    return solver;
}

void destroy_solver(NQueens **solver) {
    if (solver == NULL || *solver == NULL)
        return;

    free((*solver)->board);
    free((*solver)->columns);
    free((*solver)->diagonal1);
    free((*solver)->diagonal2);
    free(*solver);

    *solver = NULL;
}

int is_safe(const NQueens *solver, size_t row, size_t column) {
    size_t diagonal1 = row + column;
    size_t diagonal2 = row + solver->size - 1 - column;

    return !solver->columns[column] &&
           !solver->diagonal1[diagonal1] &&
           !solver->diagonal2[diagonal2];
}

void print_board(const NQueens *solver) {
    for (size_t row = 0; row < solver->size; row++) {
        for (size_t column = 0; column < solver->size; column++)
            printf("%c ", solver->board[row] == (int)column ? 'Q' : '.');

        printf("\n");
    }

    printf("\n");
}

void solve(NQueens *solver, size_t row, int print_solutions) {
    if (row == solver->size) {
        solver->solutions++;

        if (print_solutions)
            print_board(solver);

        return;
    }

    for (size_t column = 0; column < solver->size; column++) {
        if (!is_safe(solver, row, column))
            continue;

        size_t diagonal1 = row + column;
        size_t diagonal2 = row + solver->size - 1 - column;

        solver->board[row] = (int)column;
        solver->columns[column] = 1;
        solver->diagonal1[diagonal1] = 1;
        solver->diagonal2[diagonal2] = 1;

        solve(solver, row + 1, print_solutions);

        solver->board[row] = -1;
        solver->columns[column] = 0;
        solver->diagonal1[diagonal1] = 0;
        solver->diagonal2[diagonal2] = 0;
    }
}

size_t count_solutions(size_t size) {
    if (size == 0)
        return 0;

    NQueens *solver = create_solver(size);

    solve(solver, 0, 0);

    size_t solutions = solver->solutions;

    destroy_solver(&solver);

    return solutions;
}

int main(void) {
    const size_t n = 8;

    NQueens *solver = create_solver(n);

    solve(solver, 0, 1);

    printf("Total solutions: %zu\n", solver->solutions);

    destroy_solver(&solver);

    return EXIT_SUCCESS;
}
