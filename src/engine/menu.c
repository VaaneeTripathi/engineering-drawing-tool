#include <stdio.h>
#include <stdlib.h>
#include "../include/save_file.h"
#include "../include/menu.h"
#include "../include/polyhedron.h"

// Function to display the main menu and handle user input
void welcome_user() {
    int choice;
    Polyhedron *current_polyhedron = NULL;

    while (1) {
        printf("\n--- Welcome to the 3D Polyhedron Tool ---\n");
        printf("1. Create a new polyhedron\n");
        printf("2. Modify an existing polyhedron\n");
        printf("3. Traverse saved files\n");
        printf("4. Save current polyhedron\n");
        printf("5. Load a polyhedron from file\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                current_polyhedron = run_polyhedron_creation();
                break;
            case 2:
                modify_existing_polyhedron(current_polyhedron);
                break;
            case 3:
                traverse_saved_files();
                break;
            case 4:
                save_current_polyhedron(current_polyhedron);
                break;
            case 5:
                current_polyhedron = load_polyhedron_from_file_menu();
                break;
            case 6:
                printf("Exiting the program. Goodbye!\n");
                if (current_polyhedron) free(current_polyhedron);
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Function to modify an existing polyhedron
void modify_existing_polyhedron(Polyhedron *poly) {
    if (!poly) {
        printf("No polyhedron loaded to modify.\n");
        return;
    }

    int option;
    do {
        printf("\nChoose an operation for polyhedron '%s':\n", poly->name);
        printf("1. Scale\n2. Translate\n3. Rotate\n4. Cross-section\n5. Projections\n6. Detect Holes\n7. Hidden Lines\n8. Save & Exit\n");
        scanf("%d", &option);

        switch (option) {
            case 1:
                test_scaling(poly);
                break;
            case 2:
                test_translation(poly);
                break;
            case 3:
                test_rotation(poly);
                break;
            case 4:
                cross_section_oblique(poly);
                break;
            case 5:
                top_view_projection(poly);
                break;
            case 6:
                detect_holes_in_polyhedron(poly);
                break;
            case 7: {
                Vertex viewer_position = get_viewer_position();
                classify_edge_visibility(poly->bsp_root, viewer_position);
                print_visibility(poly);
                break;
            }
            case 8:
                save_polyhedron_to_file(poly, poly->name);
                printf("Polyhedron saved and exiting modification.\n");
                return;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != 8);
}

// Prompts the user to enter a filename and saves the current polyhedron
void save_current_polyhedron(Polyhedron *poly) {
    if (!poly) {
        printf("No polyhedron loaded to save.\n");
        return;
    }
    char filename[50];
    printf("Enter filename to save polyhedron: ");
    scanf("%s", filename);
    save_polyhedron_to_file(poly, filename);
}

// Prompts the user to load a polyhedron file
Polyhedron* load_polyhedron_from_file_menu() {
    char filename[50];
    printf("Enter filename to load polyhedron: ");
    scanf("%s", filename);
    Polyhedron *poly = load_polyhedron_from_file(filename);
    if (poly) {
        printf("Polyhedron '%s' loaded successfully.\n", poly->name);
    } else {
        printf("Failed to load polyhedron.\n");
    }
    return poly;
}
