// polygon.h
#ifndef POLYGON_H
#define POLYGON_H


#include "edge.h"
#include "vertex.h"

typedef struct {
    Vertex **vertices;      // Array of vertices
    int vertex_count;       // Number of vertices in the polygon
    Vertex normal;         // Normal vector for orientation
    Vertex centroid;       // Centroid of the polygon
    Edge **edges;           // Optional: Array of edges if edges need to be stored here
    int edge_count;         // Number of edges (optional)
} Polygon;

// Function to calculate the normal of a polygon (optional but helpful)
void calculate_normal(Polygon *polygon);
void calculate_centroid(Polygon *polygon);

#endif
