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

// Validate the minimum number of edges
int validate_minimum_edges(int vertex_count, int edge_count) {
    int min_edges = vertex_count - 1;
    if (edge_count < min_edges) {
        printf("Error: A polyhedron with %d vertices requires at least %d edges.\n",
               vertex_count, min_edges);
        return 0;
    }
    return 1;
}

// Validate the maximum number of edges for given vertices
int validate_edge_count(int vertex_count, int edge_count) {
    int max_edges = (vertex_count * (vertex_count - 1)) / 2;
    if (edge_count > max_edges) {
        printf("Error: Too many edges for the given number of vertices.\n");
        return 0;
    }
    return 1;
}

// Main polyhedron creation function with "Go Back" functionality
void run_polyhedron_creation() {
    int step = 1;  // Track the current step
    int vertex_count = 0, edge_count = 0, face_count = 0;
    Polyhedron *poly = NULL;

    while (1) {
        switch (step) {
            case 1:
                // Step 1: Get number of vertices
                vertex_count = prompt_for_int("How many vertices?", 1, 100);
                if (vertex_count == -2) { step = 1; continue; }  // Retry
                if (vertex_count == -1) { step = 1; continue; }  // Go back
                step++;  // Move to the next step
                break;

            case 2:
                // Step 2: Get number of edges
                edge_count = prompt_for_int("How many edges?", 1, 200);
                if (edge_count == -2) { step = 1; continue; }  // Retry
                if (edge_count == -1) { step--; continue; }    // Go back

                // Validate edge count
                if (!validate_edge_count(vertex_count, edge_count) ||
                    !validate_minimum_edges(vertex_count, edge_count)) {
                    int choice = show_menu("What would you like to do?");
                    if (choice == 1) { step = 1; continue; }  // Retry from start
                    if (choice == 2) { step--; continue; }    // Go back
                    if (choice == 3) exit(0);
                }
                step++;  // Move to the next step
                break;

            case 3:
                // Step 3: Get number of faces
                face_count = prompt_for_int("How many faces?", 1, 100);
                if (face_count == -2) { step = 1; continue; }  // Retry
                if (face_count == -1) { step--; continue; }    // Go back

                // Validate face count logic
                if (face_count > edge_count) {
                    printf("Error: Faces cannot exceed the number of edges.\n");
                    int choice = show_menu("What would you like to do?");
                    if (choice == 1) { step = 1; continue; }  // Retry from start
                    if (choice == 2) { step--; continue; }    // Go back
                    if (choice == 3) exit(0);
                }
                // Create the polyhedron
                poly = create_polyhedron(vertex_count, edge_count, face_count);
                step++;  // Move to the next step
                break;

            case 4:
                // Step 4: Input vertices
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
                step++;  // Move to the next step
                break;

            case 5:
                // Step 5: Input edges
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
                step++;  // Move to the next step
                break;

            case 6:
                // Step 6: Input faces
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
                step++;  // Move to the next step
                break;

            case 7:
                // Step 7: Validate Euler's formula
                if (!validate_euler(poly)) {
                    printf("Error: Euler's formula not satisfied.\n");
                    free(poly);
                    step = 1;  // Restart on failure
                    continue;
                }

                // Print polyhedron summary
                printf("\n--- Polyhedron Summary ---\n");
                print_polyhedron(poly);

                // Clean up
                free(poly->vertices);
                free(poly->edges);
                free(poly->faces);
                free(poly);
                return;  // Exit the function after successful completion
        }
    }
}

int main() {
    signal(SIGINT, handle_interrupt);
    run_polyhedron_creation();
    return 0;
}
