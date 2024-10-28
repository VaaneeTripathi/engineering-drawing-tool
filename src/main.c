#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "/home/vaanee/cs-coded/work/engineering-drawing-tool/src/include/polyhedron.h"


// Function prototypes
void welcome_user();
void create_new_polyhedron();
void modify_existing_polyhedron();
void traverse_saved_files();

// Main program to start user interaction
int main() {
    welcome_user();
    return 0;
}

void welcome_user() {
    int choice;

    while (1) {
        printf("\n--- Welcome to the 3D Polyhedron Tool ---\n");
        printf("1. Create a new polyhedron\n");
        printf("2. Modify an existing polyhedron\n");
        printf("3. Traverse saved files\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_new_polyhedron();
                break;
            case 2:
                modify_existing_polyhedron();
                break;
            case 3:
                traverse_saved_files();
                break;
            case 4:
                printf("Exiting the program. Goodbye!\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

























































































































































// int main() {
//     signal(SIGINT, handle_interrupt);  // Handle Ctrl+C gracefully
//     Polyhedron* poly = run_polyhedron_creation();         // Start the process
//     test_scaling(poly);
//     test_translation(poly);
//     test_rotation(poly);      // Apply rotation


//     top_view_projection(poly);         // Top view projection
//     front_view_projection(poly);       // Front view projection
//     side_view_projection(poly);        // Side view projection
//     test_cross_section_oblique(poly);  // Oblique cross-section
//     Vertex viewer_position = get_viewer_position();
//     classify_edge_visibility(poly->bsp_root, viewer_position);
//     print_visibility(poly);
//     detect_holes_in_polyhedron(poly);
        
//     // Cleanup
//     free(poly->vertices);
//     free(poly->edges);
//     free(poly->faces);
//     free(poly);
//     return 0;
// }
