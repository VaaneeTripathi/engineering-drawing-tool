// face.h
#ifndef FACE_H
#define FACE_H

#include "vertex.h"
#include "edge.h"

typedef struct {
    Edge **edges;        // Array of pointers to edges that make up this face
    int edge_count;      // Number of edges in the face
    Vertex normal;      // Normal vector of the face
    Vertex centroid;    // Centroid of the face
} Face;

// Functions to calculate normal and centroid
void calculate_face_normal(Face *face);
void calculate_face_centroid(Face *face);

#endif
