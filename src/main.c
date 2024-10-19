#include <stdio.h>
#include <stdlib.h>
#include "../include/polyhedron.h"

// Helper function to clear input buffer
void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main() {
    int vertex_count, edge_count, face_count;

    printf("Welcome to the Polyhedron Creation Tool!\n");

    // Get polyhedron details from the user
    printf("How many vertices does your polyhedron have? ");
    scanf("%d", &vertex_count);

    printf("How many edges does your polyhedron have? ");
    scanf("%d", &edge_count);

    printf("How many faces does your polyhedron have? ");
    scanf("%d", &face_count);

    // Create a new polyhedron
    Polyhedron *poly = create_polyhedron(vertex_count, edge_count, face_count);

    printf("\n--- Enter Vertex Coordinates ---\n");
    for (int i = 0; i < vertex_count; i++) {
        float x, y, z;
        printf("Vertex V%d (x y z): ", i);
        scanf("%f %f %f", &x, &y, &z);

        if (is_valid_vertex(poly, x, y, z)) {
            printf("Duplicate vertex detected! Please enter unique coordinates.\n");
            i--;  // Retry current vertex
            continue;
        }

        add_vertex(poly, x, y, z);
    }

    printf("\n--- Define Edges ---\n");
    for (int i = 0; i < edge_count; i++) {
        int start, end;
        printf("Edge E%d connects vertices (start end): ", i);
        scanf("%d %d", &start, &end);

        if (start == end) {
            printf("Invalid edge! Start and end vertices cannot be the same.\n");
            i--;  // Retry current edge
            continue;
        }

        if (is_valid_edge(poly, start, end)) {
            printf("Duplicate edge detected! Please enter unique edges.\n");
            i--;  // Retry current edge
            continue;
        }

        add_edge(poly, start, end);
    }

    printf("\n--- Define Faces ---\n");
    for (int i = 0; i < face_count; i++) {
        int edge_count;
        printf("How many edges in face F%d? ", i);
        scanf("%d", &edge_count);

        int *edges = (int *)malloc(edge_count * sizeof(int));
        printf("Enter the edge indices for face F%d: ", i);
        for (int j = 0; j < edge_count; j++) {
            scanf("%d", &edges[j]);
        }

        add_face(poly, edges, edge_count);
        free(edges);

        printf("Face F%d defined with %d edges.\n", i, edge_count);
    }

    // Validate the polyhedron using Euler's formula
    if (!validate_euler(poly)) {
        printf("Error: The polyhedron does not satisfy Euler's formula. Exiting.\n");
        free(poly);
        return 1;  // Exit with failure
    }

    printf("\n--- Polyhedron Summary ---\n");
    print_polyhedron(poly);

    // Free memory
    free(poly->vertices);
    free(poly->edges);
    free(poly->faces);
    free(poly);

    return 0;
}
