#ifndef POLYHEDRON_H
#define POLYHEDRON_H

#include "vertex.h"
#include "edge.h"
#include "face.h"
#include "bsp_node.h"

typedef struct {
    Vertex **vertices;   // List of pointers to vertices
    Edge **edges;        // List of pointers to edges
    Face **faces;        // List of pointers to faces
    int vertex_count;    // Number of vertices
    int edge_count;      // Number of edges
    int face_count;      // Number of faces
    BSPNode *bsp_root;   // Root of the BSP tree
} Polyhedron;

// Function prototypes
Polyhedron* create_polyhedron(int vertex_count, int edge_count, int face_count);
void add_vertex(Polyhedron *poly, float x, float y, float z);
void add_edge(Polyhedron *poly, int start, int end);
void print_polyhedron(Polyhedron *poly);

#endif // POLYHEDRON_H
