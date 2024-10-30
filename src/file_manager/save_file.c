#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <dirent.h>
#include "../include/polyhedron.h"
#include "../include/save_file.h"

// Save polyhedron to a custom binary file
void save_polyhedron_to_file(Polyhedron *poly, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    // Write file header
    FileHeader header;
    snprintf(header.name, sizeof(header.name), "%s", poly->name);
    time_t now = time(NULL);
    strftime(header.creation_date, sizeof(header.creation_date), "%Y-%m-%d %H:%M:%S", localtime(&now));
    header.file_size = sizeof(FileHeader) + poly->vertex_count * sizeof(Vertex) + poly->edge_count * sizeof(Edge) + poly->face_count * sizeof(Face);
    fwrite(&header, sizeof(FileHeader), 1, file);

    // Write vertices
    fwrite(poly->vertices, sizeof(Vertex), poly->vertex_count, file);

    // Write edges
    fwrite(poly->edges, sizeof(Edge), poly->edge_count, file);

    // Write faces
    for (int i = 0; i < poly->face_count; i++) {
        Face *face = poly->faces[i];
        fwrite(&face->edge_count, sizeof(int), 1, file);
        fwrite(face->edges, sizeof(Edge *), face->edge_count, file);
    }

    fclose(file);
    printf("Polyhedron saved to %s successfully.\n", filename);
}

// Load polyhedron from a custom binary file
Polyhedron* load_polyhedron_from_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }

    // Read file header
    FileHeader header;
    fread(&header, sizeof(FileHeader), 1, file);
    printf("Loading polyhedron: %s, created on %s\n", header.name, header.creation_date);

    // Allocate and initialize polyhedron
    Polyhedron *poly = (Polyhedron *)malloc(sizeof(Polyhedron));
    strncpy(poly->name, header.name, sizeof(poly->name));
    poly->vertex_count = header.vertex_count;
    poly->edge_count = header.edge_count;
    poly->face_count = header.face_count;

    // Allocate memory for vertices, edges, and faces
    poly->vertices = (Vertex **)malloc(poly->vertex_count * sizeof(Vertex *));
    for (int i = 0; i < poly->vertex_count; i++) {
        poly->vertices[i] = (Vertex *)malloc(sizeof(Vertex));
    }
    fread(poly->vertices, sizeof(Vertex), poly->vertex_count, file);

    poly->edges = (Edge **)malloc(poly->edge_count * sizeof(Edge *));
    for (int i = 0; i < poly->edge_count; i++) {
        poly->edges[i] = (Edge *)malloc(sizeof(Edge));
    }
    fread(poly->edges, sizeof(Edge), poly->edge_count, file);

    poly->faces = (Face **)malloc(poly->face_count * sizeof(Face *));
    for (int i = 0; i < poly->face_count; i++) {
        Face *face = (Face *)malloc(sizeof(Face));
        fread(&face->edge_count, sizeof(int), 1, file);
        face->edges = (Edge **)malloc(face->edge_count * sizeof(Edge *));
        fread(face->edges, sizeof(Edge *), face->edge_count, file);
        poly->faces[i] = face;
    }

    fclose(file);
    printf("Polyhedron loaded from %s successfully.\n", filename);
    return poly;
}

void traverse_saved_files() {
    const char *directory = "./saved_polyhedrons/";
    DIR *dir = opendir(directory);

    if (!dir) {
        perror("Could not open directory");
        return;
    }

    struct dirent *entry;
    printf("\n--- Saved Polyhedron Files ---\n");

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // Regular file
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
    printf("\nEnd of saved files.\n");
}