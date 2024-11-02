#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../include/polyhedron.h"
#include "../include/save_file.h"

// Ensure the save directory exists
void ensure_directory_exists(const char *directory) {
    struct stat st = {0};
    if (stat(directory, &st) == -1) {
        mkdir(directory, 0777);  // Create with rwx permissions for owner
    }
}
void save_polyhedron_to_file(Polyhedron *poly, char filename[50]) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    // Write header information
    time_t now = time(NULL);
    fprintf(file, "Polyhedron: %s\n", poly->name);
    fprintf(file, "Creation Date: %s", ctime(&now));
    fprintf(file, "Vertices: %d Edges: %d Faces: %d BSP Nodes: %d\n",
            poly->vertex_count, poly->edge_count, poly->face_count, poly->node_count);

    // Save vertices with their coordinates
    for (int i = 0; i < poly->vertex_count; i++) {
        fprintf(file, "Vertex %d: %.2f %.2f %.2f\n", i, 
                poly->vertices[i]->x, poly->vertices[i]->y, poly->vertices[i]->z);
    }

    // Save edges with start and end vertex indices
    for (int i = 0; i < poly->edge_count; i++) {
        fprintf(file, "Edge %d: Start %d End %d\n", i,
                poly->edges[i]->start_index, poly->edges[i]->end_index);
    }

    // Save faces with edges that make up each face
    for (int i = 0; i < poly->face_count; i++) {
        fprintf(file, "Face %d: Edge Count %d\n", i, poly->faces[i]->edge_count);
        for (int j = 0; j < poly->faces[i]->edge_count; j++) {
            int edge_index = poly->faces[i]->edges[j]->start_index;  
            fprintf(file, "%d ", edge_index);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Polyhedron saved to %s successfully.\n", filename);
}

Polyhedron* load_polyhedron_from_file(char filename[50]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }


    Polyhedron *poly = (Polyhedron *)malloc(sizeof(Polyhedron));
    poly->bsp_nodes = NULL;
    strcpy(filename,  poly->name);

    // Read header
    fscanf(file, "Polyhedron: %s\n", poly->name);
    char creation_date[100];
    fgets(creation_date, sizeof(creation_date), file);
    fscanf(file, "Vertices: %d Edges: %d Faces: %d BSP Nodes: %d\n",
           &poly->vertex_count, &poly->edge_count, &poly->face_count, &poly->node_count);

    // Initialize arrays
    poly->vertices = (Vertex **)malloc(poly->vertex_count * sizeof(Vertex *));
    poly->edges = (Edge **)malloc(poly->edge_count * sizeof(Edge *));
    poly->faces = (Face **)malloc(poly->face_count * sizeof(Face *));
    poly->bsp_nodes = (BSPNode **)malloc(poly->node_count * sizeof(BSPNode *));

    // Load vertices
    for (int i = 0; i < poly->vertex_count; i++) {
        poly->vertices[i] = (Vertex *)malloc(sizeof(Vertex));
        fscanf(file, "Vertex %*d: %f %f %f\n", 
               &poly->vertices[i]->x, &poly->vertices[i]->y, &poly->vertices[i]->z);
    }

    // Load edges
    for (int i = 0; i < poly->edge_count; i++) {
        poly->edges[i] = (Edge *)malloc(sizeof(Edge));
        fscanf(file, "Edge %*d: Start %d End %d\n",
               &poly->edges[i]->start_index, &poly->edges[i]->end_index);
    }

    // Load faces
    for (int i = 0; i < poly->face_count; i++) {
        int edge_count;
        fscanf(file, "Face %*d: Edge Count %d\n", &edge_count);
        poly->faces[i] = (Face *)malloc(sizeof(Face));
        poly->faces[i]->edge_count = edge_count;
        poly->faces[i]->edges = (Edge **)malloc(edge_count * sizeof(Edge *));
        for (int j = 0; j < edge_count; j++) {
            int edge_index;
            fscanf(file, "%d", &edge_index);
            poly->faces[i]->edges[j] = poly->edges[edge_index];
        }
    }

    fclose(file);
    return poly;
}

void traverse_saved_files() {
    const char *directory = "saved_polyhedrons";
    DIR *dir;
    struct dirent *entry;

    dir = opendir(directory);
    if (dir == NULL) {
        printf("Error: Could not open directory %s\n", directory);
        return;
    }

    printf("Saved polyhedron files in '%s':\n", directory);
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            printf("- %s\n", entry->d_name);
        }
    }

    closedir(dir);
}