# Maze Treasure Map Encoder/Decoder

This C++ project encodes a maze traversal path into an image using steganography and decodes the path to visualize the solution. It uses breadth-first search (BFS) to compute the shortest path from a start location in a maze image and encodes those distances into the low-order bits of a base image.

---

## Project Files

- `main.cpp` - Main program that runs encoding and decoding on sample images.
- `treasureMap.cpp` / `treasureMap.h` - Implements the maze traversal, encoding logic, and rendering methods.
- `decoder.cpp` / `decoder.h` - Extracts and reconstructs the solution path from the encoded image.
- `stack.cpp` / `stack.h` - Custom stack data structure used in traversal logic.
- `queue.cpp` / `queue.h` - Custom queue used for breadth-first search.
- `deque.cpp` / `deque.h` - Custom double-ended queue supporting the queue implementation.
- `Makefile` - Build automation script.
- `cs221util/` - Image utility library (includes `PNG`, `RGBAPixel`, and `lodepng`).
- `images/` - Contains input images and saves output images.

---

## Build Instructions

1. Open a terminal and navigate to the project directory.
2. Run the following command to build the project:

```bash
make
```

This compiles the source files and produces the `pa2` executable.

---

## Running the Program

To run the program:

```bash
./pa2
```

This will:

- Load the maze and base images from the `images/` folder
- Perform BFS traversal and encode the distance data into the image
- Generate and save the following output images in the `images/` folder:

  - `zdesembedded.png` - Base image with encoded path data
  - `zdesgreyedmaze.png` - Grayscaled visualization of the maze
  - `zdessoln.png` - Decoded shortest path from the start
  - `zdessolnmaze.png` - Solution path overlaid on the maze

---

## Dependencies

- C++17 or later
- No external libraries required
- Image functionality is handled by the provided `cs221util` utilities

---

## Learning Objectives

This project demonstrates:

- Grid traversal using breadth-first search (BFS)
- Image-based steganography through low-order bit encoding
- Pixel manipulation and image processing
- Implementation of core data structures (stack, queue, deque)

---

## Clean Up

To remove compiled object files and the executable, run:

```bash
make clean
```
