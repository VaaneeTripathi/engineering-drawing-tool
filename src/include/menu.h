// menu.h
#ifndef MENU_H
#define MENU_H

#include "polyhedron.h"
#include "save_file.h"

// Function to display the main menu and handle user input
void welcome_user();

// Function to modify an existing polyhedron, offering options for transformations, viewing, etc.
void modify_existing_polyhedron();

// Function to save the currently loaded polyhedron to a file
void save_current_polyhedron(Polyhedron *poly);

// Function to load a polyhedron from a specified file
Polyhedron* load_polyhedron_from_file_menu();

#endif  // MENU_H
