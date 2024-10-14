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
        add_vertex(poly, x, y, z);
    }

    printf("\n--- Define Edges ---\n");
    for (int i = 0; i < edge_count; i++) {
        int start, end;
        printf("Edge E%d connects vertices (start end): ", i);
        scanf("%d %d", &start, &end);

        // Validate edge input
        if (start < 0 || start >= vertex_count || end < 0 || end >= vertex_count) {
            printf("Invalid vertices! Please enter valid vertex indices.\n");
            i--;  // Retry current edge
            clear_input();  // Clear buffer to avoid input issues
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

            // Validate edge index
            if (edges[j] < 0 || edges[j] >= poly->edge_count) {
                printf("Invalid edge index! Please enter a valid index.\n");
                j--;  // Retry current edge
                clear_input();  // Clear buffer to avoid input issues
                continue;
            }
        }

        add_face(poly, edges, edge_count);
        free(edges);

        printf("Face F%d defined with %d edges.\n", i, edge_count);
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
