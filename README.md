# 🎮 cub3D

A 3D maze game using raycasting, inspired by Wolfenstein 3D. Built in C using the MiniLibX graphics library.

## 🎯 Overview
This project implements a first-person perspective maze game using raycasting techniques. Created as part of the 42 school curriculum.

## ⚠️ Notice to 42 Students
This repository serves as a reference. Please:
- Understand the code before using it
- Don't copy without comprehension
- Use it to learn concepts, not to bypass learning

## ✨ Features
- **3D Rendering**: Realistic perspective using raycasting
- **Interactive Controls**: 
  - `W`, `A`, `S`, `D` for movement
  - Arrow keys for camera rotation
  - `ESC` to exit
- **Textured Environment**:
  - Unique textures for each wall direction (N, S, E, W)
  - Customizable floor and ceiling colors
- **Configurable Maps**: Custom `.cub` files for level design

## 🕹️ Controls
| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` | Rotate camera left |
| `→` | Rotate camera right |
| `ESC` | Exit game |

## 🗺️ Map Configuration
Maps use `.cub` files with the following format:

### Texture Paths
```
NO ./path_to_north_texture.xpm
SO ./path_to_south_texture.xpm
WE ./path_to_west_texture.xpm
EA ./path_to_east_texture.xpm
```

### Colors (RGB)
```
F 220,100,0    # Floor color
C 225,30,0     # Ceiling color
```

### Map Layout
```
1111111
1000001
1000N01
1111111
```

### Map Elements
- `1`: Wall
- `0`: Empty space
- `N/S/E/W`: Player start position and orientation
- ` `: Valid space (must not break map closure)

### Map Rules
- Must be surrounded by walls
- Only one player start position allowed
- No map leaks allowed

## 🔧 Technical Requirements
- Clean exit on ESC key or window closing
- Smooth window management
- No memory leaks
- Proper error handling for invalid configurations

## 🚀 Building and Running
```bash
# Compile the project
make

# Run with a map
./cub3D maps/example.cub
```

## 👥 Contributors
[Jakob Seiderer](https://github.com/JakobVaSeid)

## 📝 License
This project is part of 42 School's curriculum.

---
*Created with determination and lots of ☕*
