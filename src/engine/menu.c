#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "../include/save_file.h"
#include "../include/menu.h"
#include "../include/polyhedron.h"
#include "../include/properties.h"

// Function to display the main menu and handle user input
void welcome_user() {
    int choice;
    Polyhedron *current_polyhedron = NULL;

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
                current_polyhedron = run_polyhedron_creation();
                break;
            case 2:
                modify_existing_polyhedron(current_polyhedron);
                break;
            case 3:
                traverse_saved_files();
                break;
            case 4:
                printf("Exiting the program. Goodbye!\n");
                if (current_polyhedron) free(current_polyhedron);
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Function to list files in the saved directory and choose one to modify
void modify_existing_polyhedron() {
    // Directory where saved polyhedrons are stored
    const char *directory = "./saved_polyhedrons/";

    // Open the directory
    DIR *dir = opendir(directory);
    if (!dir) {
        printf("Could not open saved polyhedron directory.\n");
        return;
    }

    // Display the list of polyhedron files
    struct dirent *entry;
    int file_count = 0;
    char filenames[100][256];  // To store file names, adjust size if necessary

    printf("\nAvailable polyhedrons:\n");
    while ((entry = readdir(dir)) != NULL) {
        // Skip '.' and '..'
        if (entry->d_name[0] == '.') continue;

        snprintf(filenames[file_count], sizeof(filenames[file_count]), "%s", entry->d_name);
        printf("%d. %s\n", file_count + 1, filenames[file_count]);
        file_count++;
    }
    closedir(dir);

    if (file_count == 0) {
        printf("No saved polyhedrons available to modify.\n");
        return;
    }

    // Prompt the user to select a polyhedron file
    int choice;
    printf("\nEnter the number of the polyhedron you wish to modify: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > file_count) {
        printf("Invalid selection.\n");
        return;
    }

    // Build the full filepath and load the selected polyhedron
    char filepath[300];
    snprintf(filepath, sizeof(filepath), "%s%s", directory, filenames[choice - 1]);
    Polyhedron *poly = load_polyhedron_from_file(filepath);
    if (!poly) {
        printf("Failed to load polyhedron from '%s'.\n", filepath);
        return;
    }
    strcpy(poly->name, filenames[choice - 1]);
    printf("Polyhedron '%s' loaded successfully.\n", poly->name);

    // Modification menu
    int option;
    do {
        printf("\nChoose an operation for polyhedron '%s':\n", poly->name);
        printf("1. Scale\n2. Translate\n3. Rotate\n4. Cross-section\n5. Orthographic Projections\n");
        printf("6. Detect Holes\n7. Hidden Lines\n8. Calculate Physical Properties\n9. Save & Exit\n");
        printf("Enter option: ");
        scanf("%d", &option);

        switch (option) {
        case 1:  // Scaling
        float scale_x;
        float scale_y;
        float scale_z;
            printf("Enter scaling factors for x y z: ");
            if (scanf("%f %f %f", &scale_x, &scale_y, &scale_z) == 3) {
                scale_polyhedron(poly, scale_x, scale_y, scale_z);
                print_polyhedron(poly);
            } else {
                printf("Invalid input. Please enter three numbers.\n");
            }
            break;
            case 2:
                float tx;
                float ty;
                float tz;
            printf("Enter translation factors for x y z: ");
            if (scanf("%f %f %f", &tx, &ty, &tz) == 3) {
                translate_polyhedron(poly, tx, ty, tz);
                print_polyhedron(poly);
            } else {
                printf("Invalid input. Please enter three numbers.\n");
            }
            break;
            case 3:
                float angle;
                char axis;
                printf("Enter angle in degrees =");
                scanf( "%f", &angle);
                printf("Enter axis of rotation (x y z) = ");
                scanf("%s", &axis);
                rotate_polyhedron(poly, angle, axis);
                print_polyhedron(poly);
                break;
            case 4:
                cross_section_oblique(poly);
                break;
            case 5:
                top_view_projection(poly);
                front_view_projection(poly);
                side_view_projection(poly);
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
            case 8:{
                calculate_polyhedron_properties(poly);
            }
            case 9:
                save_polyhedron_to_file(poly, poly->name);
                printf("Polyhedron saved and exiting modification.\n");
                return;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != 9);

    free(poly);
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
