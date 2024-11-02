#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H

#include "polyhedron.h"


void initializeOpenGL();
void render_polyhedron(Polyhedron *poly);
void main_render_loop(Polyhedron *poly);

#endif