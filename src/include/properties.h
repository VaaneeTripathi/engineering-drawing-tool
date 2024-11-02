#ifndef PROPERTIES_H
#define PROPERTIES_H

#include "vertex.h"


void cross_product(Vertex *v1, Vertex *v2, Vertex *result);
float dot_product(Vertex *v1, Vertex *v2);
void calculate_polyhedron_properties(Polyhedron *poly);

#endif