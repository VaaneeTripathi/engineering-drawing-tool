# Engineering Drawing Tool

## Introduction
The Engineering Drawing Tool is an  interactive software application designed to assist with creating and analyzing polyhedral structures for engineering purposes. It provides users with various options to create, manipulate, visualize, and calculate properties of polyhedrons. This tool is ideal for students, educators, and professionals who need a reliable and interactive way to work with geometric models in a computational environment.

## Features
- **Polyhedron Creation**: Build polyhedrons from vertices, edges, and faces.
- **Polyhedron Manipulation**: Allow one to rotate, translate, scale polyhedrons. Additionally, one can also derive orthographic projections as well as cross-sections along planes at oblique angles.
- **Polyhedron Exploration**: Detect holes and edge visibility
- **Volume, Center of Mass, and Moment of Inertia Calculation**: Compute essential physical properties of polyhedral structures.
- **Rendering and Visualization**: Render polyhedrons using OpenGL for real-time visualization.
- **File Management**: Save and load polyhedral models for continued work.
- **Modular Design**: The code is modular, separating functionality into clearly defined components for better maintainability and scalability.

## Directory Structure
```plaintext
engineering-drawing-tool/
├── build/                  # Compiled binaries and object files
│   ├── bin/                # Executable output directory
│   └── obj/                # Compiled object files
├── docs/                   # Documentation files
├── examples/               # Example polyhedron files
|── saved_polyhedrons/      # Saved polyhedron models (.poly files)
├── src/                    # Source code files
│   ├── include/            # Header files
│   ├── engine/             # Core engine for polyhedron creation and manipulation
│   ├── file_manager/       # File management for loading and saving polyhedrons
│   └── render/             # Rendering engine for OpenGL visualization                
└── tests/                  # Unit and integration tests
```

## Installation and Usage

### Prerequisites

- Compiler: GCC or any C compiler.
- OpenGL: Required for rendering.
- Libraries: Ensure GLEW, GLFW, and GLU are installed on your system.

### Steps

1. Clone the repository:

```git clone https://github.com/VaaneeTripathi/engineering-drawing-tool.git```

2. Navigate to the project directory:

```
cd engineering-drawing-tool 
```

3. Navigate to build directory:
```
cd build/
```

4. Build the files
```
make 
```
5. Run them
```
make run
```

## Workflow 
Upon starting the Engineering Drawing Tool, you are presented with a main menu offering four primary options to manage and interact with polyhedrons. These options guide the workflow of creating, modifying, and managing polyhedron files.

### Main Menu Options
**Create a New Polyhedron:** This option allows you to build a polyhedron from scratch by specifying vertices, edges, and faces. After defining these elements, you are prompted with the following choices:
- Save: Save the created polyhedron to the file system.
- Discard: Discard the current polyhedron without saving.
- Retry: Start over, clearing all current inputs for vertices, edges, and faces.

**Modify Existing Polyhedron:** This option allows you to select a previously saved polyhedron and perform various operations on it. After selecting a polyhedron, a secondary menu appears with around nine modification options (e.g., scaling, rotating, translating). Each option may prompt you for specific parameters, such as axis of rotation, scaling factor, or translation vector, depending on the selected operation.

**Traverse Saved Files:** This option allows you to browse through previously saved polyhedron files. You can view file names, details, and load any saved polyhedron into the tool for further modification or analysis.

**Exit:** Select this option to safely exit the application.

## Examples to Use

## MIT License 
Copyright (c) [2024] [Vaanee Tripathi / Engineering Drawing Tool]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
