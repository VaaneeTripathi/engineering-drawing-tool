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
        mkdir(directory, 0700);  // Create with rwx permissions for owner
    }
}

void save_polyhedron_to_file(Polyhedron *poly, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    // Write header
    time_t now = time(NULL);
    fprintf(file, "Polyhedron: %s\n", poly->name);
    fprintf(file, "Creation Date: %s", ctime(&now));
    fprintf(file, "Vertices: %d Edges: %d Faces: %d BSP Nodes: %d\n",
            poly->vertex_count, poly->edge_count, poly->face_count, poly->node_count);

    // Save BSP nodes
    for (int i = 0; i < poly->node_count; i++) {
        BSPNode *node = poly->bsp_nodes[i];
        int left_index = -1, right_index = -1;

        // Find indices of left and right child nodes
        for (int j = 0; j < poly->node_count; j++) {
            if (poly->bsp_nodes[j] == node->left) left_index = j;
            if (poly->bsp_nodes[j] == node->right) right_index = j;
        }

        fprintf(file, "Node %d: Plane [%f, %f, %f, %f] Left %d Right %d\n",
                i, node->plane[0], node->plane[1], node->plane[2], node->plane[3], left_index, right_index);

        // Write face data
        if (node->face) {
            fprintf(file, "Face %d: Edge Count %d\n", i, node->face->edge_count);
            for (int e = 0; e < node->face->edge_count; e++) {
                fprintf(file, "%d ", node->face->edges[e]->start_index);
                fprintf(file, "%d ", node->face->edges[e]->end_index);
            }
            fprintf(file, "\n");
        }
    }

    fclose(file);
    printf("Polyhedron saved to %s successfully.\n", filename);
}


Polyhedron* load_polyhedron_from_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }

    Polyhedron *poly = (Polyhedron *)malloc(sizeof(Polyhedron));
    poly->bsp_nodes = NULL;  // Initialize as needed later

    // Read header
    fscanf(file, "Polyhedron: %s\n", poly->name);
    char creation_date[100];
    fgets(creation_date, sizeof(creation_date), file);
    fscanf(file, "Vertices: %d Edges: %d Faces: %d BSP Nodes: %d\n",
           &poly->vertex_count, &poly->edge_count, &poly->face_count, &poly->node_count);

    poly->vertices = (Vertex **)malloc(poly->vertex_count * sizeof(Vertex *));
    poly->edges = (Edge **)malloc(poly->edge_count * sizeof(Edge *));
    poly->faces = (Face **)malloc(poly->face_count * sizeof(Face *));
    poly->bsp_nodes = (BSPNode **)malloc(poly->node_count * sizeof(BSPNode *));

    // Read BSP nodes
    for (int i = 0; i < poly->node_count; i++) {
        BSPNode *node = (BSPNode *)malloc(sizeof(BSPNode));
        int left_index, right_index;
        fscanf(file, "Node %*d: Plane [%f, %f, %f, %f] Left %d Right %d\n",
               &node->plane[0], &node->plane[1], &node->plane[2], &node->plane[3],
               &left_index, &right_index);

        // Set left and right pointers after all nodes are created
        poly->bsp_nodes[i] = node;
        node->left = (left_index >= 0) ? poly->bsp_nodes[left_index] : NULL;
        node->right = (right_index >= 0) ? poly->bsp_nodes[right_index] : NULL;

        // Read face data if present
        int edge_count;
        if (fscanf(file, "Face %*d: Edge Count %d\n", &edge_count) == 1) {
            node->face = (Face *)malloc(sizeof(Face));
            node->face->edge_count = edge_count;
            node->face->edges = (Edge **)malloc(edge_count * sizeof(Edge *));
            for (int e = 0; e < edge_count; e++) {
                int start, end;
                fscanf(file, "%d %d", &start, &end);
                Edge *edge = (Edge *)malloc(sizeof(Edge));
                edge->start_index = start;
                edge->end_index = end;
                node->face->edges[e] = edge;
            }
        } else {
            node->face = NULL;
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