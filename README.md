*This project has been created as part of the 42 curriculum by ylebee, peserre-s.*

# cub3D

## Description

**cub3D** is a 3D maze exploration project written in C as part of the 42 curriculum. Inspired by *Wolfenstein 3D*, it uses ray-casting to create a first-person view of a map with textured walls, a configurable floor and ceiling, and real-time player movement.

The program reads a scene description file (`.cub`), validates its configuration and map, then opens a graphical window using MiniLibX.

The project focuses on ray-casting, parsing, map validation, event handling, graphics programming, and memory management in C.

## Features

### Mandatory part

- First-person 3D rendering based on ray-casting.
- Different wall textures for the North, South, East, and West sides.
- Configurable floor and ceiling colors using RGB values.
- Player movement in four directions.
- Camera rotation with the left and right arrow keys.
- Wall collision handling.
- Map and scene validation before starting the game.
- Clean exit using `ESC` or the window close button.

### Bonus part

The bonus build adds:

- A minimap.
- Sliding doors that can open and close.
- Mouse-controlled camera rotation.

The project also contains a weapon overlay and a laser effect triggered by a mouse click.

## Controls

| Input | Action |
| --- | --- |
| `W` | Move forward |
| `S` | Move backward |
| `A` | Move left |
| `D` | Move right |
| `Left Arrow` | Rotate left |
| `Right Arrow` | Rotate right |
| `ESC` | Close the game |
| `Left Mouse Button` | Trigger the laser effect |
| `Mouse Movement` *(bonus)* | Rotate the camera horizontally |
| `Space` *(bonus)* | Open or close the door in front of the player |

## Requirements

The project is designed to be built on Linux and requires:

- A C compiler (`cc`).
- GNU Make.
- X11 development headers and libraries.
- MiniLibX for Linux, available in `libs/minilibx-linux/`.

On Debian or Ubuntu, the usual build dependencies can be installed with:

```bash
sudo apt update
sudo apt install build-essential libx11-dev libxext-dev
```

The repository contains the Libft sources in `libs/Libft/`. The Makefile builds Libft and MiniLibX before linking the game. Make sure the MiniLibX source directory is present at the path expected by the Makefile: `libs/minilibx-linux/`.

## Compilation

Clone or download the repository, then run the commands from the project root.

### Mandatory

```bash
make
```

This creates the `cub3D` executable.

### Bonus

```bash
make bonus
```

This compiles the bonus configuration, including the minimap, doors, and mouse camera controls.

When switching between mandatory and bonus builds, clean the previous build first:

```bash
make fclean
make          # mandatory
```

Or:

```bash
make fclean
make bonus    # bonus
```

## Execution

The program takes one argument: a scene file with the `.cub` extension.

Run it from the project root so that the relative texture paths in the scene file are resolved correctly:

```bash
./cub3D maps/map_test.cub
```

Other example maps are available in the `maps/` directory:

- `maps/map_test.cub`
- `maps/map_test_2.cub` *(bonus door map)*
- `maps/map_test_3.cub` *(bonus door map)*

## Scene file format

A `.cub` file contains texture paths, floor and ceiling colors, and the map. The map must be the last element in the file.

Example:

```text
NO ./textures/wall1.xpm
SO ./textures/wall2.xpm
WE ./textures/wall3.xpm
EA ./textures/wall4.xpm
DO ./textures/doors.xpm

F 25,25,25
C 0,0,0

111111
100001
10N001
100001
111111
```

The scene identifiers are:

| Identifier | Meaning |
| --- | --- |
| `NO` | North wall texture |
| `SO` | South wall texture |
| `WE` | West wall texture |
| `EA` | East wall texture |
| `F` | Floor color in RGB format |
| `C` | Ceiling color in RGB format |
| `DO` | Door texture *(bonus only)* |

The map uses the following characters:

| Character | Meaning |
| --- | --- |
| `1` | Wall |
| `0` | Empty space |
| `N` | Player starting position, facing North |
| `S` | Player starting position, facing South |
| `E` | Player starting position, facing East |
| `W` | Player starting position, facing West |
| `D` | Door *(bonus only)* |
| Space | Empty area outside the playable map; preserved during parsing |

Map requirements:

- The map must be enclosed by walls.
- Exactly one player starting position must be provided.
- Floor and ceiling colors use three comma-separated RGB values, each in the range `0-255`.
- Texture paths must point to valid XPM files.
- For the bonus configuration, provide the `DO` texture and use `D` for door tiles.

## Project structure

```text
cub3D/
├── include/              # Main project header
├── libs/
│   ├── Libft/            # Custom C library
│   └── minilibx-linux/   # MiniLibX source code
├── maps/                 # Example .cub scene files
├── textures/             # Wall, door, and weapon textures
├── srcs/
│   ├── parsing/          # Scene parsing and map validation
│   ├── render/           # Ray-casting and 3D rendering
│   ├── player/           # Player movement and camera rotation
│   ├── events/           # Keyboard and window events
│   ├── textures/         # Texture loading and management
│   ├── weapon/           # Weapon overlay
│   └── bonus/            # Minimap, doors, mouse and laser features
└── Makefile
```

## Resources

- **42 - cub3D subject (version 12.0):** the project specification provided by the 42 curriculum.
- **MiniLibX documentation:** the manual pages included in `libs/minilibx-linux/man/` and the `mlx.h` header in the MiniLibX source directory.
- **Lode's Computer Graphics Tutorial - Raycasting:** https://lodev.org/cgtutor/raycasting.html
- **Permadi - Ray-Casting Tutorial:** https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/
- **GNU Make manual:** https://www.gnu.org/software/make/manual/
- **C library and math references:** the relevant system manual pages, including `man 3 math`.

### AI usage

AI tools, including ChatGPT, were used as learning and review aids during the project. They helped clarify ray-casting and MiniLibX concepts, discuss parsing and rendering issues, and identify edge cases that could be turned into tests. AI suggestions were treated as guidance and reviewed by the project authors. The authors remain responsible for the implementation, the final technical decisions, and understanding the code submitted for evaluation.

## Authors

- **ylebee**
- **peserre-s**
