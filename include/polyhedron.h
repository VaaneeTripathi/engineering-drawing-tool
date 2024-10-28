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
void add_face(Polyhedron *poly, int *edge_indices, int edge_count);
void print_polyhedron(Polyhedron *poly);
int is_valid_vertex(Polyhedron *poly, float x, float y, float z);
int is_valid_edge(Polyhedron *poly, int start, int end);
int validate_euler(Polyhedron *poly);
void scale_polyhedron(Polyhedron *poly, float scale_x, float scale_y, float scale_z) ;
void translate_polyhedron(Polyhedron *poly, float dx, float dy, float dz); 
void rotate_polyhedron(Polyhedron *poly, float angle, char axis);
void top_view_projection(Polyhedron *poly);
void front_view_projection(Polyhedron *poly);
void side_view_projection(Polyhedron *poly);
void cross_section_oblique(Polyhedron *poly, float px, float py, float pz, float nx, float ny, float nz);
void classify_edge_visibility(BSPNode *node, Vertex viewer_position);
void print_visibility(Polyhedron *poly);


#endif // POLYHEDRON_H
