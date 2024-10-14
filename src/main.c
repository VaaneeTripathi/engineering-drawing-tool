// main.c
#include <stdio.h>
#include <stdlib.h>
#include "../include/polyhedron.h"

int main() {
    int vertex_count, edge_count;

    // Get polyhedron details from the user
    printf("Enter the number of vertices: ");
    scanf("%d", &vertex_count);
    printf("Enter the number of edges: ");
    scanf("%d", &edge_count);

    // Create a new polyhedron
    Polyhedron *poly = create_polyhedron(vertex_count, edge_count, 0);

    // Input vertices
    for (int i = 0; i < vertex_count; i++) {
        float x, y, z;
        printf("Enter coordinates for vertex V%d (x y z): ", i);
        scanf("%f %f %f", &x, &y, &z);
        add_vertex(poly, x, y, z);
    }

    // Input edges
    for (int i = 0; i < edge_count; i++) {
        int start, end;
        printf("Enter edge E%d (start end): ", i);
        scanf("%d %d", &start, &end);
        add_edge(poly, start, end);
    }

    // Print the polyhedron
    print_polyhedron(poly);

    // Free memory (for simplicity, not all memory is freed here)
    free(poly->vertices);
    free(poly->edges);
    free(poly);

    return 0;
}
