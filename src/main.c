#include <stdio.h>
#include <stdlib.h>
#include "../include/polyhedron.h"

// Helper function to clear the input buffer
void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Menu to navigate: Retry, Go Back, or Exit
int show_menu(const char *message) {
    printf("%s\n", message);
    printf("[1] Retry\n[2] Go Back to Previous Step\n[3] Exit Program\n");
    int choice;
    scanf("%d", &choice);
    clear_input();
    return choice;
}

// Input validation loop with error handling and navigation
int prompt_for_int(const char *prompt, int min, int max) {
    int value;
    while (1) {
        printf("%s (between %d and %d): ", prompt, min, max);
        if (scanf("%d", &value) == 1 && value >= min && value <= max) {
            clear_input();
            return value;
        } else {
            clear_input();
            int choice = show_menu("Invalid input. What would you like to do?");
            if (choice == 2) return -1;  // Go back to the previous step
            if (choice == 3) exit(0);    // Exit the program
        }
    }
}

// Main program logic
int main() {
    printf("Welcome to the Polyhedron Creation Tool!\n");

    // Get number of vertices
    int vertex_count = prompt_for_int("How many vertices does your polyhedron have?", 1, 100);
    if (vertex_count == -1) return main();  // Go back to the start

    // Get number of edges
    int edge_count = prompt_for_int("How many edges does your polyhedron have?", 1, 200);
    if (edge_count == -1) return main();  // Go back to the start

    // Get number of faces
    int face_count = prompt_for_int("How many faces does your polyhedron have?", 1, 100);
    if (face_count == -1) return main();  // Go back to the start

    Polyhedron *poly = create_polyhedron(vertex_count, edge_count, face_count);

    printf("\n--- Enter Vertex Coordinates ---\n");
    for (int i = 0; i < vertex_count; i++) {
        float x, y, z;
        while (1) {
            printf("Vertex V%d (x y z): ", i);
            if (scanf("%f %f %f", &x, &y, &z) == 3) {
                if (is_duplicate_vertex(poly, x, y, z)) {
                    int choice = show_menu("Duplicate vertex detected. What would you like to do?");
                    if (choice == 2) return main();  // Go back to the start
                    if (choice == 3) exit(0);        // Exit the program
                } else {
                    add_vertex(poly, x, y, z);
                    break;
                }
            } else {
                clear_input();
                int choice = show_menu("Invalid input. What would you like to do?");
                if (choice == 2) return main();  // Go back to the start
                if (choice == 3) exit(0);        // Exit the program
            }
        }
    }

    printf("\n--- Define Edges ---\n");
    for (int i = 0; i < edge_count; i++) {
        int start, end;
        while (1) {
            printf("Edge E%d connects vertices (start end): ", i);
            if (scanf("%d %d", &start, &end) == 2) {
                if (start == end) {
                    int choice = show_menu("Invalid edge! Start and end vertices cannot be the same.");
                    if (choice == 2) return main();
                    if (choice == 3) exit(0);
                } else if (is_duplicate_edge(poly, start, end)) {
                    int choice = show_menu("Duplicate edge detected. What would you like to do?");
                    if (choice == 2) return main();
                    if (choice == 3) exit(0);
                } else {
                    add_edge(poly, start, end);
                    break;
                }
            } else {
                clear_input();
                int choice = show_menu("Invalid input. What would you like to do?");
                if (choice == 2) return main();
                if (choice == 3) exit(0);
            }
        }
    }

    printf("\n--- Define Faces ---\n");
    for (int i = 0; i < face_count; i++) {
        int edge_count;
        printf("How many edges in face F%d? ", i);
        scanf("%d", &edge_count);
        int *edges = (int *)malloc(edge_count * sizeof(int));

        for (int j = 0; j < edge_count; j++) {
            while (1) {
                printf("Enter edge index for face F%d: ", i);
                scanf("%d", &edges[j]);
                if (edges[j] < 0 || edges[j] >= poly->edge_count) {
                    int choice = show_menu("Invalid edge index. What would you like to do?");
                    if (choice == 2) return main();
                    if (choice == 3) exit(0);
                } else {
                    break;
                }
            }
        }
        add_face(poly, edges, edge_count);
        free(edges);
    }

    if (!validate_euler(poly)) {
        printf("Error: The polyhedron does not satisfy Euler's formula. Exiting.\n");
        free(poly);
        return 1;
    }

    printf("\n--- Polyhedron Summary ---\n");
    print_polyhedron(poly);

    free(poly->vertices);
    free(poly->edges);
    free(poly->faces);
    free(poly);

    return 0;
}
