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

## Documentation

## License 