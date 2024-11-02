#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/polyhedron.h"
#include "../include/vertex.h"

void initializeOpenGL() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(-1);
    }

    GLFWwindow *window = glfwCreateWindow(800, 600, "Polyhedron Renderer", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    glewInit();
}

void render_polyhedron(Polyhedron *poly) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set camera
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0/600.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Draw vertices
    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0);
    for (int i = 0; i < poly->vertex_count; i++) {
        glVertex3f(poly->vertices[i]->x, poly->vertices[i]->y, poly->vertices[i]->z);
    }
    glEnd();

    // Draw edges
    glColor3f(0.0, 0.5, 1.0);
    glBegin(GL_LINES);
    for (int i = 0; i < poly->edge_count; i++) {
        Vertex *start = poly->vertices[poly->edges[i]->start_index];
        Vertex *end = poly->vertices[poly->edges[i]->end_index];
        glVertex3f(start->x, start->y, start->z);
        glVertex3f(end->x, end->y, end->z);
    }
    glEnd();

    // Flush buffer
    glFlush();
}

void main_render_loop(Polyhedron *poly) {
    GLFWwindow *window = glfwGetCurrentContext();

    while (!glfwWindowShouldClose(window)) {
        render_polyhedron(poly);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
