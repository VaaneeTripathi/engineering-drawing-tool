#ifndef FACE_H
#define FACE_H

#include "edge.h"

typedef struct {
    Edge **edges;    // Array of pointers to edges
    int edge_count;  // Number of edges in the face
} Face;

#endif // FACE_H
