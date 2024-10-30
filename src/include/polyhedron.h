#ifndef POLYHEDRON_H
#define POLYHEDRON_H

#include "vertex.h"
#include "edge.h"
#include "face.h"
#include "bsp_node.h"


typedef struct Polyhedron {
    char name[50];           // Name of the polyhedron
    int vertex_count;
    int edge_count;
    int face_count;
    int node_count;          // Number of BSP nodes, if needed
    Vertex **vertices;       // Array of vertices
    Edge **edges;            // Array of edges
    Face **faces;            // Array of faces
    BSPNode **bsp_nodes;     // Array of BSP nodes if using BSP tree
    BSPNode *bsp_root;       // Root of BSP tree
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
void cross_section_oblique(Polyhedron *poly);
void classify_edge_visibility(BSPNode *node, Vertex viewer_position);
void print_visibility(Polyhedron *poly);
int detect_holes_in_face(Face *face);
void detect_holes_in_polyhedron(Polyhedron *poly);
Polyhedron *run_polyhedron_creation();
void handle_interrupt(int sig);
void clear_input();
int show_menu(const char *message);
int prompt_for_int(const char *prompt, int min, int max);
int validate_minimum_edges(int vertex_count, int edge_count);
int validate_edge_count(int vertex_count, int edge_count);
Vertex get_viewer_position();


#endif // POLYHEDRON_H
