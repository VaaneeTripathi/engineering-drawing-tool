#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "../include/polyhedron.h"

// Handle Ctrl+C interruptions gracefully
void handle_interrupt(int sig) {
    printf("\nProgram interrupted. Exiting...\n");
    exit(0);
}

// Clear input buffer
void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Menu for retry, go back, or exit options
int show_menu(const char *message) {
    printf("%s\n", message);
    printf("[1] Retry\n[2] Go Back to Previous Step\n[3] Exit Program\n");
    int choice;
    scanf("%d", &choice);
    clear_input();
    return choice;
}

// Prompt for integer input with validation
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
            if (choice == 1) return -2;  // Retry the entire process
            if (choice == 2) return -1;  // Go back to the previous step
            if (choice == 3) exit(0);    // Exit the program
        }
    }
}

// Validate minimum edges for the given vertices
int validate_minimum_edges(int vertex_count, int edge_count) {
    int min_edges = vertex_count - 1;
    if (edge_count < min_edges) {
        printf("Error: A polyhedron with %d vertices requires at least %d edges.\n",
               vertex_count, min_edges);
        return 0;
    }
    return 1;
}

// Validate maximum edges based on vertices
int validate_edge_count(int vertex_count, int edge_count) {
    int max_edges = (vertex_count * (vertex_count - 1)) / 2;
    if (edge_count > max_edges) {
        printf("Error: Too many edges for the given number of vertices.\n");
        return 0;
    }
    return 1;
}

// Main polyhedron creation loop
Polyhedron *run_polyhedron_creation() {
    int step = 1;  // Track the current step

    int vertex_count = 0, edge_count = 0, face_count = 0;
    Polyhedron *poly = NULL;

    while (step <= 4) {
        switch (step) {
            case 1:
                vertex_count = prompt_for_int("How many vertices?", 1, 100);
                if (vertex_count == -2) continue;  // Restart
                if (vertex_count == -1) { step--; continue; }  // Go back
                step++;  // Proceed to the next step
                break;

            case 2:
                edge_count = prompt_for_int("How many edges?", 1, 200);
                if (edge_count == -2) continue;
                if (edge_count == -1) { step--; continue; }

                if (!validate_edge_count(vertex_count, edge_count) ||
                    !validate_minimum_edges(vertex_count, edge_count)) {
                    int choice = show_menu("What would you like to do?");
                    if (choice == 1) continue;  // Restart
                    if (choice == 2) { step--; continue; }  // Go back
                    if (choice == 3) exit(0);
                }
                step++;
                break;

            case 3:
                face_count = prompt_for_int("How many faces?", 1, 100);
                if (face_count == -2) continue;
                if (face_count == -1) { step--; continue; }

                if (face_count > edge_count) {
                    printf("Error: Faces cannot exceed the number of edges.\n");
                    int choice = show_menu("What would you like to do?");
                    if (choice == 1) continue;
                    if (choice == 2) { step--; continue; }
                    if (choice == 3) exit(0);
                }
                poly = create_polyhedron(vertex_count, edge_count, face_count);
                step++;
                break;

            case 4:
                printf("\n--- Enter Vertex Coordinates ---\n");
                for (int i = 0; i < vertex_count; i++) {
                    float x, y, z;
                    while (1) {
                        printf("Vertex V%d (x y z): ", i);
                        if (scanf("%f %f %f", &x, &y, &z) == 3) {
                            if (is_valid_vertex(poly, x, y, z)) {
                                printf("Duplicate vertex detected. Try again.\n");
                                continue;
                            }
                            add_vertex(poly, x, y, z);
                            break;
                        } else {
                            clear_input();
                            printf("Invalid input. Try again.\n");
                        }
                    }
                }
                step++;
                break;
        }
    }

    // Proceed with edge and face input once vertices are entered
    printf("\n--- Define Edges ---\n");
    for (int i = 0; i < edge_count; i++) {
        int start, end;
        while (1) {
            printf("Edge E%d (start end): ", i);
            if (scanf("%d %d", &start, &end) == 2 &&
                start != end && start >= 0 && end >= 0 &&
                start < vertex_count && end < vertex_count) {
                if (is_valid_edge(poly, start, end)) {
                    printf("Duplicate edge detected. Try again.\n");
                    continue;
                }
                add_edge(poly, start, end);
                break;
            } else {
                clear_input();
                printf("Invalid edge. Try again.\n");
            }
        }
    }

    // Face input logic
    printf("\n--- Define Faces ---\n");
    for (int i = 0; i < face_count; i++) {
        int edge_count;
        printf("How many edges in face F%d? ", i);
        scanf("%d", &edge_count);
        int *edges = (int *)malloc(edge_count * sizeof(int));

        for (int j = 0; j < edge_count; j++) {
            while (1) {
                printf("Edge index for face F%d: ", i);
                scanf("%d", &edges[j]);
                if (edges[j] >= 0 && edges[j] < poly->edge_count) {
                    break;
                } else {
                    printf("Invalid edge index. Try again.\n");
                }
            }
        }
        add_face(poly, edges, edge_count);
        free(edges);
    }

    if (!validate_euler(poly)) {
        printf("Error: Euler's formula not satisfied.\n");
        free(poly);
    }

    printf("\n--- Polyhedron Summary ---\n");
    print_polyhedron(poly);

    return poly;
}

// Testing scaling
void test_scaling(Polyhedron *poly) {
    float scale_factor_x;
    float scale_factor_y;
    float scale_factor_z;
    printf("Enter the scaling factor: ");
    scanf("%f %f %f", &scale_factor_x, &scale_factor_y, &scale_factor_z);

    scale_polyhedron(poly, scale_factor_x, scale_factor_y, scale_factor_z);
    printf("\n--- Polyhedron After Scaling ---\n");
    print_polyhedron(poly);
}


int main() {
    signal(SIGINT, handle_interrupt);  // Handle Ctrl+C gracefully
    Polyhedron* poly = run_polyhedron_creation();         // Start the process
    test_scaling(poly);
        // Cleanup
    free(poly->vertices);
    free(poly->edges);
    free(poly->faces);
    free(poly);
    return 0;
}
