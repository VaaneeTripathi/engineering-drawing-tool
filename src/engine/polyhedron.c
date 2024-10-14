#include "../../include/polyhedron.h"
#include "../../include/edge.h"
#include <stdlib.h>
#include <stdio.h>

// Create a new polyhedron
Polyhedron* create_polyhedron(int vertex_count, int edge_count, int face_count) {
    Polyhedron *poly = (Polyhedron *)malloc(sizeof(Polyhedron));
    poly->vertices = (Vertex **)malloc(vertex_count * sizeof(Vertex *));
    poly->edges = (Edge **)malloc(edge_count * sizeof(Edge *));
    poly->faces = (Face **)malloc(face_count * sizeof(Face *));
    poly->vertex_count = 0;
    poly->edge_count = 0;
    poly->face_count = 0;
    poly->bsp_root = NULL;  // BSP tree will be built later
    return poly;
}

// Add a vertex to the polyhedron
void add_vertex(Polyhedron *poly, float x, float y, float z) {
    Vertex *v = (Vertex *)malloc(sizeof(Vertex));
    v->x = x;
    v->y = y;
    v->z = z;
    poly->vertices[poly->vertex_count++] = v;
}

// Add an edge to the polyhedron
void add_edge(Polyhedron *poly, int start, int end) {
    Edge *e = (Edge *)malloc(sizeof(Edge));
    e->start_index = start;
    e->end_index = end;
    poly->edges[poly->edge_count++] = e;
}

// Print the polyhedron's structure
void print_polyhedron(Polyhedron *poly) {
    printf("Polyhedron with %d vertices, %d edges:\n", poly->vertex_count, poly->edge_count);

    printf("Vertices:\n");
    for (int i = 0; i < poly->vertex_count; i++) {
        printf("V%d: (%.2f, %.2f, %.2f)\n", i,
               poly->vertices[i]->x, poly->vertices[i]->y, poly->vertices[i]->z);
    }

    printf("Edges:\n");
    for (int i = 0; i < poly->edge_count; i++) {
        printf("E%d: V%d -> V%d\n", i,
               poly->edges[i]->start_index, poly->edges[i]->end_index);
    }
}

