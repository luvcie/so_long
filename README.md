# So Long

A 2D top-down adventure game built with C and the MiniLibX graphics library. Navigate through maps, collect vinyls, and find your way to the exit!

## Overview

So Long is a simple 2D game where the player must collect all collectibles (vinyls) scattered throughout the map before being able to exit. The game features sprite-based graphics and keyboard controls for movement.

## Objective

- **Collect** all vinyls (C) on the map
- **Navigate** to the exit (E) 
- **Complete** the level with the minimum number of moves

## Controls

| Key | Action |
|-----|--------|
| `W` / `↑` / `K` | Move Up |
| `S` / `↓` / `J` | Move Down |
| `A` / `←` / `H` | Move Left |
| `D` / `→` / `L` | Move Right |
| `ESC` | Exit Game |

*Multiple control schemes supported for different preferences!*

## Map Elements

- **`P`** - Player starting position
- **`C`** - Collectible vinyls
- **`E`** - Exit (only accessible after collecting all vinyls)
- **`1`** - Walls
- **`0`** - Empty floor space

## Visual Features

### Dynamic Wall Generation
The game features a sophisticated wall rendering system:
- **8 different wall sprites** stored in an array (`wall[8]`)
- **Procedural generation** using position-based randomization
- Each wall tile uses the formula `(x * 7 + y * 13) % 8` to determine its sprite variant
- Creates **natural-looking diversity** without repetitive patterns

This approach ensures that identical maps will always look the same while providing visual variety across different wall sections.

## Building & Running

### Prerequisites
- GCC compiler
- MiniLibX library
- X11 development libraries (Linux)

### Compilation
```bash
make
```

### Usage
```bash
./so_long [map_file.ber]
```

### Example
```bash
./so_long apartment.ber
```

## Project Structure

```
so_long/
├── src/
│   ├── main.c              # Main game loop and initialization
│   ├── parse_map.c         # Map file parsing and validation
│   ├── rendermap.c         # Rendering engine and graphics
│   ├── player_movement.c   # Player controls and game logic
│   ├── load_sprites.c      # Sprite loading and management
│   ├── cleanup.c           # Memory management and cleanup
│   ├── utils.c             # Utility functions
│   └── get_next_line.c     # File reading utility
├── sprites/                # Game sprite assets
├── libft/                  # Custom C library
├── minilibx-linux/         # Graphics library
├── Makefile               # Build configuration
└── *.ber                  # Map files
```

## Graphics Engine

- **Sprite-based rendering** with 64x64 pixel tiles
- **Efficient tile mapping** system
- **Real-time position updates** during gameplay
- **Memory-optimized** image management

## Features

- Move counter - Track your efficiency
- Win condition validation - Must collect all vinyls first
- Error handling - Robust map validation
- Memory management - Clean resource cleanup
- Cross-platform key bindings

## Map Format

Maps are stored in `.ber` files with a simple character-based format following specific rules:

### Map Requirements
- **Rectangular shape** - All rows must have the same length
- **Wall boundaries** - The entire map must be surrounded by walls (`1`)
- **Single player** - Exactly one player starting position (`P`)
- **Single exit** - Exactly one exit point (`E`)
- **Collectibles** - At least one vinyl to collect (`C`)
- **Valid path** - There must be a valid path to collect all vinyls and reach the exit

### Example Map Structure
```
111111111111111
1P0001100000001
100001100C00001
100000000000001
100C00000000111
111000000000001
100000000000001
100000111110001
100000100000001
100C00100000001
111100100000001
100000000000001
10000000000000E1
111111111111111
```

### Character Legend
- `1` - Wall 
- `0` - Empty floor space
- `P` - Player starting position
- `C` - Collectible
- `E` - Exit door

### File Format Notes
- Each line represents a row in the map
- No empty lines allowed within the map
- The file extension must be `.ber`
- Maps should be designed to be solvable (all vinyls reachable)

---

*Built as part of the 42 School curriculum - A project focusing on graphics programming, game logic, and memory management in C.*
