#include <stdio.h>
#include <stdlib.h>
#include "../include/polyhedron.h"

int main() {
    int vertex_count, edge_count, face_count;

    // Get polyhedron details from the user
    printf("Enter the number of vertices: ");
    scanf("%d", &vertex_count);
    printf("Enter the number of edges: ");
    scanf("%d", &edge_count);
    printf("Enter the number of faces: ");
    scanf("%d", &face_count);

    // Create a new polyhedron
    Polyhedron *poly = create_polyhedron(vertex_count, edge_count, face_count);

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

    // Input faces
    for (int i = 0; i < face_count; i++) {
        int edge_count;
        printf("Enter the number of edges in face F%d: ", i);
        scanf("%d", &edge_count);

        int *edges = (int *)malloc(edge_count * sizeof(int));
        printf("Enter the edge indices: ");
        for (int j = 0; j < edge_count; j++) {
            scanf("%d", &edges[j]);
        }

        add_face(poly, edges, edge_count);
        free(edges);
    }

    // Print the polyhedron
    print_polyhedron(poly);

    // Free memory (partial cleanup for simplicity)
    free(poly->vertices);
    free(poly->edges);
    free(poly->faces);
    free(poly);

    return 0;
}
