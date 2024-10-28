#ifndef BSP_NODE_H
#define BSP_NODE_H

#include "face.h"

typedef struct BSPNode {
    Face *face;                // A face stored at this node (can be NULL)
    float plane[4];             // Plane equation: Ax + By + Cz + D = 0
    struct BSPNode *left;       // Space in front of the plane
    struct BSPNode *right;      // Space behind the plane
} BSPNode;

// Function to create a new BSP node
BSPNode* create_node(Face *face, float plane[4]);

#endif // BSP_NODE_H
