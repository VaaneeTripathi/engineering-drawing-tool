#include <math.h>
#include "../../include/polyhedron.h"
#include "../../include/edge.h"
#include "../../include/vertex.h"
#include "../../include/polygon.h"
#include <stdlib.h>
#include <stdio.h>


#define M_PI 3.14159265358979323846
#define DEG_TO_RAD(angle) ((angle) * M_PI / 180.0)

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



// Function to rotate a polyhedron
void rotate_polyhedron(Polyhedron *poly, float angle, char axis) {
    float rad = DEG_TO_RAD(angle);  // Convert angle to radians
    float cos_theta = cos(rad);
    float sin_theta = sin(rad);

    for (int i = 0; i < poly->vertex_count; i++) {
        if (poly->vertices[i]) {
            float x = poly->vertices[i]->x;
            float y = poly->vertices[i]->y;
            float z = poly->vertices[i]->z;

            if (axis == 'x' || axis == 'X') {  // Rotate around X-axis
                poly->vertices[i]->y = y * cos_theta - z * sin_theta;
                poly->vertices[i]->z = y * sin_theta + z * cos_theta;
            } else if (axis == 'y' || axis == 'Y') {  // Rotate around Y-axis
                poly->vertices[i]->x = x * cos_theta + z * sin_theta;
                poly->vertices[i]->z = -x * sin_theta + z * cos_theta;
            } else if (axis == 'z' || axis == 'Z') {  // Rotate around Z-axis
                poly->vertices[i]->x = x * cos_theta - y * sin_theta;
                poly->vertices[i]->y = x * sin_theta + y * cos_theta;
            }
        }
    }
}

// Function to generate a top view projection (XY plane)
void top_view_projection(Polyhedron *poly) {
    printf("\n--- Top View (Projection onto XY plane) ---\n");
    for (int i = 0; i < poly->vertex_count; i++) {
        printf("Vertex V%d: (%.2f, %.2f)\n", i, poly->vertices[i]->x, poly->vertices[i]->y);
    }
}

// Function to generate a front view projection (YZ plane)
void front_view_projection(Polyhedron *poly) {
    printf("\n--- Front View (Projection onto YZ plane) ---\n");
    for (int i = 0; i < poly->vertex_count; i++) {
        printf("Vertex V%d: (%.2f, %.2f)\n", i, poly->vertices[i]->y, poly->vertices[i]->z);
    }
}

// Function to generate a side view projection (XZ plane)
void side_view_projection(Polyhedron *poly) {
    printf("\n--- Side View (Projection onto XZ plane) ---\n");
    for (int i = 0; i < poly->vertex_count; i++) {
        printf("Vertex V%d: (%.2f, %.2f)\n", i, poly->vertices[i]->x, poly->vertices[i]->z);
    }
}

// Function to calculate cross-section with an oblique plane
// Plane is defined by a point (px, py, pz) and a normal vector (nx, ny, nz)
void cross_section_oblique(Polyhedron *poly, float px, float py, float pz, float nx, float ny, float nz) {
    printf("\n--- Cross-Section at Oblique Angle ---\n");
    
    for (int i = 0; i < poly->edge_count; i++) {
        Vertex *v1 = poly->vertices[poly->edges[i]->start_index];
        Vertex *v2 = poly->vertices[poly->edges[i]->end_index];

        // Debug print for vertices
        printf("Edge %d: Start Vertex (%.2f, %.2f, %.2f), End Vertex (%.2f, %.2f, %.2f)\n", i, v1->x, v1->y, v1->z, v2->x, v2->y, v2->z);

        // Direction vector of the edge
        float dx = v2->x - v1->x;
        float dy = v2->y - v1->y;
        float dz = v2->z - v1->z;

        // Print direction vector
        printf("Direction vector of edge %d: (%.2f, %.2f, %.2f)\n", i, dx, dy, dz);

        // Dot product to find the t parameter for the line-plane intersection
        float dot1 = nx * (px - v1->x) + ny * (py - v1->y) + nz * (pz - v1->z);
        float dot2 = nx * dx + ny * dy + nz * dz;

        // Print dot products
        printf("Edge %d: dot1 = %.2f, dot2 = %.2f\n", i, dot1, dot2);

        if (fabs(dot2) > 1e-6) {  // Avoid division by zero
            float t = dot1 / dot2;
            printf("Edge %d: t = %.2f\n", i, t);

            if (t >= 0.0 && t <= 1.0) {  // Intersection point lies on the edge
                float ix = v1->x + t * dx;
                float iy = v1->y + t * dy;
                float iz = v1->z + t * dz;
                printf("Intersection at Edge %d: (%.2f, %.2f, %.2f)\n", i, ix, iy, iz);
            } else {
                printf("No intersection on Edge %d (t is out of range)\n", i);
            }
        } else {
            printf("Edge %d is parallel to the plane, no intersection\n", i);
        }
    }
}

// Function to classify edge visibility using the BSP tree
void classify_edge_visibility(BSPNode *node, Vertex viewer_position) {
    if (!node) return;

    // Calculate vector from face centroid to viewer position
    Vertex normal = node->face->normal;  // Use face normal for orientation
    Vertex to_viewer = {
        viewer_position.x - node->face->centroid.x,
        viewer_position.y - node->face->centroid.y,
        viewer_position.z - node->face->centroid.z
    };

    // Dot product to determine if the face is facing the viewer
    float dot_product = normal.x * to_viewer.x + normal.y * to_viewer.y + normal.z * to_viewer.z;

    if (dot_product > 0) {  // If positive, face is toward the viewer
        // Traverse the left (front) subtree first
        classify_edge_visibility(node->left, viewer_position);

        // Set all edges as visible for faces facing the viewer
        for (int i = 0; i < node->face->edge_count; i++) {
            node->face->edges[i]->is_visible = 1;  // Use -> to access is_visible
            printf("Edge %d of face marked as visible.\n", i);
        }

        // Traverse the right (back) subtree after processing the front
        classify_edge_visibility(node->right, viewer_position);

    } else {  // If negative, face is away from the viewer
        // Traverse the right (back) subtree first
        classify_edge_visibility(node->right, viewer_position);

        // Set all edges as hidden for faces facing away from the viewer
        for (int i = 0; i < node->face->edge_count; i++) {
            node->face->edges[i]->is_visible = 0;
            printf("Edge %d of face marked as hidden.\n", i);
        }

        // Traverse the left (front) subtree after processing the back
        classify_edge_visibility(node->left, viewer_position);
    }
}

// Function to print the visibility status of each edge in the polyhedron
void print_visibility(Polyhedron *poly) {
    printf("\n--- Visibility Status of Polyhedron Edges ---\n");

    for (int i = 0; i < poly->face_count; i++) {
        Face *face = poly->faces[i];
        printf("Face %d:\n", i);

        for (int j = 0; j < face->edge_count; j++) {
            Edge *edge = face->edges[j];
            printf("  Edge %d (V%d -> V%d): %s\n", 
                   j, edge->start_index, edge->end_index, 
                   edge->is_visible ? "Visible" : "Hidden");
        }
    }
}
