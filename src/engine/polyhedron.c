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

// Add a face to the polyhedron using edge indices
void add_face(Polyhedron *poly, int *edge_indices, int edge_count) {
    Face *f = (Face *)malloc(sizeof(Face));
    f->edges = (Edge **)malloc(edge_count * sizeof(Edge *));
    f->edge_count = edge_count;

    for (int i = 0; i < edge_count; i++) {
        f->edges[i] = poly->edges[edge_indices[i]];
    }

    poly->faces[poly->face_count++] = f;
}

// Print the polyhedron's structure
void print_polyhedron(Polyhedron *poly) {
    printf("Polyhedron with %d vertices, %d edges, %d faces:\n", 
           poly->vertex_count, poly->edge_count, poly->face_count);

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

    printf("Faces:\n");
    for (int i = 0; i < poly->face_count; i++) {
        printf("F%d: ", i);
        for (int j = 0; j < poly->faces[i]->edge_count; j++) {
            printf("E%d ", j);
        }
        printf("\n");
    }
}

int is_valid_vertex(Polyhedron *poly, float x, float y, float z) {
    for (int i = 0; i < poly->vertex_count; i++) {
        Vertex *v = poly->vertices[i];
        if (v->x == x && v->y == y && v->z == z) {
            return 1;  // Duplicate found
        }
    }
    return 0;  // No duplicate
}

int is_valid_edge(Polyhedron *poly, int start, int end) {
    for (int i = 0; i < poly->edge_count; i++) {
        Edge *e = poly->edges[i];
        if ((e->start_index == start && e->end_index == end) ||
            (e->start_index == end && e->end_index == start)) {
            return 1;  // Duplicate found
            if (start == end) {
            printf("Invalid edge! Start and end vertices cannot be the same.\n");
            continue;  // Retry input
}
        }
    }
    return 0;  // No duplicate
}


int validate_euler(Polyhedron *poly) {
    int V = poly->vertex_count;
    int E = poly->edge_count;
    int F = poly->face_count;

    if (V - E + F != 2) {
        printf("Invalid polyhedron! Euler's formula V - E + F = 2 is not satisfied.\n");
        return 0;  // Invalid
    }
    return 1;  // Valid
}

// Function to scale the polyhedron by a factor for each axis
void scale_polyhedron(Polyhedron *poly, float scale_x, float scale_y, float scale_z) {
    for (int i = 0; i < poly->vertex_count; i++) {
        poly->vertices[i]->x *= scale_x;
        poly->vertices[i]->y *= scale_y;
        poly->vertices[i]->z *= scale_z;
    }
    printf("Polyhedron scaled successfully.\n");
}

// Function to translate a polyhedron
void translate_polyhedron(Polyhedron *poly, float dx, float dy, float dz) {
    for (int i = 0; i < poly->vertex_count; i++) {
        if (poly->vertices[i]) {  // Ensure vertex is allocated
            poly->vertices[i]->x += dx;
            poly->vertices[i]->y += dy;
            poly->vertices[i]->z += dz;
        } else {
            printf("Warning: Attempting to translate an uninitialized vertex.\n");
        }
    }
}

