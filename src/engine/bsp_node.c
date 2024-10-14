#include <stdlib.h>
#include "../../include/bsp_node.h"

BSPNode* create_node(Face *face, float plane[4]) {
    BSPNode *node = (BSPNode *)malloc(sizeof(BSPNode));
    node->face = face;
    for (int i = 0; i < 4; i++) {
        node->plane[i] = plane[i];
    }
    node->left = node->right = NULL;
    return node;
}
