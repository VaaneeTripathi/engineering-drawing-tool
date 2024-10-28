#include "/home/vaanee/cs-coded/work/engineering-drawing-tool/src/include/polygon.h"
#include <math.h>

// Function to calculate the normal vector of a polygon (assuming it's planar)
void calculate_normal(Polygon *polygon) {
    if (polygon->vertex_count < 3) return;

    Vector3 v1 = {polygon->vertices[1]->x - polygon->vertices[0]->x,
                  polygon->vertices[1]->y - polygon->vertices[0]->y,
                  polygon->vertices[1]->z - polygon->vertices[0]->z};
    Vector3 v2 = {polygon->vertices[2]->x - polygon->vertices[0]->x,
                  polygon->vertices[2]->y - polygon->vertices[0]->y,
                  polygon->vertices[2]->z - polygon->vertices[0]->z};

    // Cross product to get the normal
    polygon->normal.x = v1.y * v2.z - v1.z * v2.y;
    polygon->normal.y = v1.z * v2.x - v1.x * v2.z;
    polygon->normal.z = v1.x * v2.y - v1.y * v2.x;

    // Normalize the vector
    float magnitude = sqrt(polygon->normal.x * polygon->normal.x +
                           polygon->normal.y * polygon->normal.y +
                           polygon->normal.z * polygon->normal.z);
    if (magnitude > 0) {
        polygon->normal.x /= magnitude;
        polygon->normal.y /= magnitude;
        polygon->normal.z /= magnitude;
    }
}

// Function to calculate the centroid of a polygon
void calculate_centroid(Polygon *polygon) {
    float cx = 0, cy = 0, cz = 0;
    for (int i = 0; i < polygon->vertex_count; i++) {
        cx += polygon->vertices[i]->x;
        cy += polygon->vertices[i]->y;
        cz += polygon->vertices[i]->z;
    }
    polygon->centroid.x = cx / polygon->vertex_count;
    polygon->centroid.y = cy / polygon->vertex_count;
    polygon->centroid.z = cz / polygon->vertex_count;
}
