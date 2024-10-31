// save_file.h
#ifndef SAVE_FILE_H
#define SAVE_FILE_H

#include "polyhedron.h"

typedef struct {
    char name[50];
    char creation_date[20];
    int file_size;
    int vertex_count;      // Number of vertices in the polyhedron
    int edge_count;        // Number of edges in the polyhedron
    int face_count;        // Number of faces in the polyhedron
    int memory_size;
} FileHeader;

typedef struct {
    float plane[4];         // Plane equation Ax + By + Cz + D = 0
    int left_child_index;   // Index of the left child in the file (or -1 if none)
    int right_child_index;  // Index of the right child in the file (or -1 if none)
    int polygon_index;      // Index of the polygon in the file, -1 if not a leaf
} BSPNodeFile;

typedef struct {
    int vertex_count;
    float vertices[][3];    // Array of vertices as (x, y, z)
} PolygonFile;


void save_polyhedron_to_file(Polyhedron *poly, const char *filename);
Polyhedron* load_polyhedron_from_file(const char *filename);
void traverse_saved_files();
void ensure_directory_exists(const char *directory);
BSPNode* get_node_by_index(Polyhedron *poly, int index);
Edge* get_edge_by_index(Polyhedron *poly, int index);

#endif

