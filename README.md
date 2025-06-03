# Maze-Render-Traversal-C-
# Maze Treasure Map Encoder/Decoder

This project embeds a maze traversal path into an image using steganographic techniques and then decodes the embedded data to visualize the solution.

## Overview

- Encodes the shortest path distances from a start point in a maze image into the **low-order bits** of a base image.
- Uses **Breadth-First Search (BFS)** to traverse the maze and compute distances.
- Visualizes:
  - The embedded treasure map (`renderMap`)
  - The grayscale maze structure (`renderMaze`)
  - The decoded solution path (`decoder`)

## File Structure

- `main.cpp` — Runs a test using sample images and outputs generated visualizations.
- `treasureMap.h` — Defines the `treasureMap` class and BFS-based encoding/visualization logic.
- `stack.cpp` — Implements a basic generic `Stack` class (used in traversal or other utility code).
- `decoder.[h/cpp]` *(not included)* — Decodes the embedded image data to extract the path.
- `images/` — Folder containing input and output images:
  - `zdesmaze.png`, `zdesbase.png` (input)
  - `zdesembedded.png`, `zdessoln.png`, etc. (output)

## How It Works

1. **Initialization:**
   - Load maze and base images.
   - Start BFS from the given coordinate.
   
2. **Encoding (in `renderMap`):**
   - Store distance from the start in the RGB low bits of the base image.
   - Encoded image looks visually unchanged.

3. **Rendering Maze (`renderMaze`):**
   - Darkens maze pixels by 50%.
   - Draws a red square at the starting point.

4. **Decoding (in `decoder`):**
   - Reads back the distance values and reconstructs the shortest path.

## Requirements

- C++17 or later
- Custom image utility library `cs221util` (provides `PNG` and `RGBAPixel`)
- Input images placed in `images/` folder

## Output Examples

- `zdesembedded.png`: base image with embedded maze
- `zdessoln.png`: decoded solution path
- `zdesgreyedmaze.png`: grayscale version of the maze

## Educational Purpose

This project is commonly used to demonstrate:
- Steganography via bitwise operations on image channels
- BFS traversal in 2D grids
- Image manipulation in C++

---

Feel free to modify paths or filenames to match your project structure.
