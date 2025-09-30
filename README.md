![alt text](https://i.imgur.com/BIX7ziR.png)

# So Long

A 2D top-down adventure game built with C and the MiniLibX graphics library. Navigate through maps, collect vinyls, and find your way to the exit!

## Overview

So Long is a simple 2D game where the player must collect all collectibles (vinyls) scattered throughout the map before being able to exit. The game features sprite-based graphics, keyboard controls for movement, and robust map validation.

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

*Multiple control schemes supported (WASD, arrows, vim keys)*

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

### Bonus Features
- **On-screen move counter** - Displays move count directly in the game window
- Charcoal background with light gray text for readability

## Building & Running

### Prerequisites
- GCC compiler
- MiniLibX library
- X11 development libraries (Linux)

### Compilation
```bash
make          # Compile mandatory version
make bonus    # Compile with on-screen move counter
```

### Usage
```bash
./so_long [map_file.ber]
```

### Example
```bash
./so_long maps/apartment.ber
```

## Project Structure

```
so_long/
├── main.c                  # Main game loop and initialization
├── parse_map.c             # Map file parsing
├── validate_map.c          # Map validation (extension, walls, rectangle)
├── validate_elements.c     # Element validation (P, E, C counts)
├── rendermap.c             # Rendering engine and graphics
├── player_movement.c       # Player controls and game logic (mandatory)
├── player_movement_bonus.c # Player controls with on-screen counter
├── key_events_bonus.c      # Bonus keyboard event handling
├── display_moves_bonus.c   # On-screen move counter display
├── load_sprites.c          # Sprite loading and management
├── cleanup.c               # Memory management and cleanup
├── utils.c                 # Utility functions
├── get_next_line.c         # File reading utility
├── sprites/                # Game sprite assets (12 XPM files)
├── maps/                   # Map files and test cases
├── libft/                  # Custom C library
├── minilibx-linux/         # Graphics library
├── Makefile                # Build configuration
└── so_long.h               # Header file
```

## Graphics Engine

- **Sprite-based rendering** with 64x64 pixel tiles
- **Efficient tile mapping** system
- **Real-time position updates** during gameplay
- **Memory-optimized** image management
- **Layered rendering** - floor drawn first, then entities

## Features

### Core Features
- Move counter in terminal (mandatory) or on-screen (bonus)
- Win condition validation - Must collect all vinyls first
- Multiple control schemes (WASD, arrows, vim keys)
- Memory management - Clean resource cleanup
- Smooth window management (minimize/maximize support)

### Error Handling & Validation
The game includes comprehensive map validation:
- **File extension check** - Must be `.ber` format
- **Rectangular validation** - All rows must have equal length
- **Wall validation** - Map must be completely surrounded by walls
- **Element validation** - Exactly 1 player, 1 exit, at least 1 collectible
- **Character validation** - Only valid characters (0, 1, P, E, C) allowed
- **Proper error messages** - Clear feedback for all validation failures

## Map Format

Maps are stored in `.ber` files with a simple character-based format following specific rules:

### Map Requirements
- **Rectangular shape** - All rows must have the same length
- **Wall boundaries** - The entire map must be surrounded by walls (`1`)
- **Single player** - Exactly one player starting position (`P`)
- **Single exit** - Exactly one exit point (`E`)
- **Collectibles** - At least one vinyl to collect (`C`)
- **Valid characters** - Only `0`, `1`, `P`, `E`, `C` allowed

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
1000000000000E1
111111111111111
```

### Character Legend
- `1` - Wall 
- `0` - Empty floor space
- `P` - Player starting position
- `C` - Collectible vinyl
- `E` - Exit door

### File Format Notes
- Each line represents a row in the map
- No empty lines allowed within the map
- The file extension must be `.ber`
- Invalid maps will display specific error messages and exit cleanly

## Testing

Test maps are provided in the `maps/` directory:
- `apartment.ber` - Main playable level
- `invalidchar.ber` - Contains invalid character
- `nocollectibles.ber` - Missing collectibles
- `noexit.ber` - Missing exit
- `noplayer.ber` - Missing player
- `notrectangle.ber` - Non-rectangular shape
- `nowalls.ber` - Missing wall boundaries
- `twoplayers.ber` - Duplicate player positions

Run `./test.sh` to validate error handling across all test cases.

## Technical Details

### Memory Management
- Separate cleanup for heap memory (map array) and X11 server memory (MLX images)
- NULL checks prevent crashes during cleanup
- Proper exit handling (ESC, window close, game completion)

### Rendering Optimization
- Only redraws affected tiles during player movement (not entire map)
- Converts grid coordinates to pixel positions (grid * 64)

### File Reading
- Map file read twice: once to count lines, once to store content
- Allows proper memory allocation before reading
- Uses custom `get_next_line()` implementation

---

*Built as part of the 42 School curriculum - A project focusing on graphics programming, game logic, memory management, and input validation in C.*
