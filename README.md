*This project has been created as part of the 42 curriculum by meelma and fmoulin.*

# cub3D

## Description

cub3D is a raycasting engine inspired by the classic 1992 game Wolfenstein 3D. The project generates a dynamic, first-person perspective view inside a maze, using the raycasting technique to create a pseudo-3D representation from a 2D map.

The program reads a `.cub` scene description file that defines wall textures, floor/ceiling colors, and the map layout. It then renders an interactive window where the player can navigate the maze using keyboard controls: WASD for movement and arrow keys for camera rotation.

This project was developed as a two-person collaboration. meelma handled the file parsing, map validation, and project integration, while fmoulin developed the rendering engine, player movement, and minimap.

`Screenshot of minimap`

![cub3D screenshot](screenshots/screenshot_01.png)

### Features

- Raycasting-based 3D rendering with textured walls
- Four directional wall textures (North, South, East, West) loaded from `.xpm` files
- Configurable floor and ceiling colors via RGB values
- WASD movement with arrow key rotation
- Wall collision detection
- Minimap overlay with player position and ray visualization
- Comprehensive `.cub` file parsing with detailed error messages

## Instructions

### Prerequisites

- A Linux environment (developed and tested on Elementary OS / Ubuntu)
- `gcc`, `make`
- X11 development libraries: `sudo apt install libx11-dev libxext-dev`

### Compilation

```bash
git clone <repository-url>
cd cub3d
make
```

The Makefile will automatically download and compile MiniLibX if it is not already present.

### Usage

```bash
./cub3D path/to/map.cub
```

### Controls



### Map file format

A `.cub` file contains texture paths, color definitions, and a map. Example:

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100001
10N001
100001
111111
```

Map characters: `1` (wall), `0` (floor), `N/S/E/W` (player spawn and facing direction). Spaces are valid and represent void areas. The map must be fully enclosed by walls.

## Technical Details: Parsing

The parsing module is responsible for reading, validating, and structuring all data from the `.cub` file before the rendering engine takes over.

### Architecture

The parsing pipeline follows this order:

1. **Argument validation** — checks argument count and `.cub` file extension
2. **File reading** — reads line by line using `get_next_line`, classifying each line by type (texture, color, map, empty, invalid)
3. **Texture parsing** — extracts and validates four directional texture paths, checks `.xpm` extension and file existence, rejects duplicates
4. **Color parsing** — extracts and validates RGB values for floor and ceiling, ensures each component is a pure number in the 0–255 range, rejects duplicates
5. **Map construction** — collects map lines into a linked list, converts to a 2D array
6. **Map validation** — verifies only valid characters are present, exactly one player exists, and the map is fully enclosed by walls
7. **Player initialization** — extracts player position and direction from the map, initializes the camera plane, replaces the player character with floor

### Map closure validation

The map closure check uses a multi-step approach:

- **Edge checks** verify that the first and last rows, as well as the first and last real characters of each row, are not walkable tiles
- **Flood fill from all walkable tiles** ensures every `0` and player tile is fully enclosed. The algorithm treats walls (`1`) and spaces as barriers, and returns an error if any walkable tile reaches the edge of a row (past its string length) or the edge of the map

This approach correctly handles irregular map shapes, maps with internal rooms, and maps with spaces between wall sections, as demonstrated by the subject's own example map.

### Error handling

All error messages are written to `stderr`. The parser provides specific error messages for each failure case, including invalid characters, missing or duplicate textures/colors, unclosed maps, and malformed color values. On error, all allocated memory is properly freed before exiting.

## Resources

### References

### AI usage

AI was used during development as a code review aid. Specifically, it was used for:

- Generating test map files to cover edge cases in map validation
- Structuring the project's header files and Makefile organization

All code was written by the team members. AI was not used to generate the core logic of either the parsing or rendering modules.
