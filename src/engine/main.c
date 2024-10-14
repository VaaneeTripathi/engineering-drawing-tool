// main.c
#include <stdio.h>
#include <stdlib.h>
#include "../../include/bsp_node.h"
#include "../../include/face.h"

// Helper function to print the plane equation
void print_plane(float plane[4]) {
    printf("Plane: %.2fx + %.2fy + %.2fz + %.2f = 0\n", 
           plane[0], plane[1], plane[2], plane[3]);
}

// Simple traversal to print the BSP tree
void traverse_bsp(BSPNode *node) {
    if (node == NULL) return;

    print_plane(node->plane);
    traverse_bsp(node->left);
    traverse_bsp(node->right);
}

int main() {
    // Create a dummy face (for testing)
    Face *face = (Face *)malloc(sizeof(Face));
    face->edge_count = 0; // Empty face for now

    // Define two planes
    float plane1[4] = {1.0, 0.0, 0.0, -5.0};  // x = 5
    float plane2[4] = {0.0, 1.0, 0.0, -3.0};  // y = 3

    // Create BSP nodes
    BSPNode *root = create_node(face, plane1);
    root->left = create_node(NULL, plane2);

    // Traverse and print the BSP tree
    printf("BSP Tree Traversal:\n");
    traverse_bsp(root);

    // Free memory (for simplicity, not freeing everything here)
    free(face);
    free(root->left);
    free(root);

    return 0;
}
