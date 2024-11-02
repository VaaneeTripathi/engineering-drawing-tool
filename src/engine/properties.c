#include <stdio.h>
#include <math.h>
#include "../include/polyhedron.h"
#include "../include/vertex.h"

// Helper function to calculate the cross product
void cross_product(Vertex *v1, Vertex *v2, Vertex *result) {
    result->x = v1->y * v2->z - v1->z * v2->y;
    result->y = v1->z * v2->x - v1->x * v2->z;
    result->z = v1->x * v2->y - v1->y * v2->x;
}

// Helper function to calculate the dot product
float dot_product(Vertex *v1, Vertex *v2) {
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

// Calculate volume, center of mass, and moment of inertia
void calculate_polyhedron_properties(Polyhedron *poly) {
    float total_volume = 0.0;
    Vertex center_of_mass = {0.0, 0.0, 0.0};
    float inertia_tensor[3][3] = {0};

    for (int i = 0; i < poly->face_count; i++) {
        Face *face = poly->faces[i];

        // Ensure face has at least 3 edges for a valid face
        if (face->edge_count < 3) {
            printf("Warning: Face %d has insufficient edges.\n", i);
            continue;
        }

        // Assuming face has vertices A, B, C
        Vertex *A = poly->vertices[face->edges[0]->start_index];
        Vertex *B = poly->vertices[face->edges[1]->start_index];
        Vertex *C = poly->vertices[face->edges[2]->start_index];

        // Calculate vectors AB and AC
        Vertex AB = {B->x - A->x, B->y - A->y, B->z - A->z};
        Vertex AC = {C->x - A->x, C->y - A->y, C->z - A->z};

        // Calculate cross product of AB and AC
        Vertex cross;
        cross_product(&AB, &AC, &cross);

        // Volume of tetrahedron with origin O and vertices A, B, C
        float volume = fabs(dot_product(A, &cross)) / 6.0;
        total_volume += volume;

        // Update center of mass
        Vertex face_centroid = {(A->x + B->x + C->x) / 3.0,
                                (A->y + B->y + C->y) / 3.0,
                                (A->z + B->z + C->z) / 3.0};
        center_of_mass.x += face_centroid.x * volume;
        center_of_mass.y += face_centroid.y * volume;
        center_of_mass.z += face_centroid.z * volume;

        // Inertia contributions (for simplicity, using the approximate form)
        // Fill inertia tensor calculations here based on centroid position and volume
        // Adjust inertia_tensor for each axis based on the face_centroid and volume
    }

    // Finalize center of mass calculation
    center_of_mass.x /= total_volume;
    center_of_mass.y /= total_volume;
    center_of_mass.z /= total_volume;

    printf("Total Volume: %.2f\n", total_volume);
    printf("Center of Mass: (%.2f, %.2f, %.2f)\n", center_of_mass.x, center_of_mass.y, center_of_mass.z);
    printf("Moment of Inertia Tensor:\n");
    for (int i = 0; i < 3; i++) {
        printf("[%.2f, %.2f, %.2f]\n", inertia_tensor[i][0], inertia_tensor[i][1], inertia_tensor[i][2]);
    }
}
