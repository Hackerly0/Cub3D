# Cub3D — **Door** (Question-Door Mini-Game)

A ray-casting maze game where every **door** challenges you with a question.  
Open **all** doors to win. Mess up twice on the same door and… a **scary face** greets you 👻

Teammates: [@Hackerly0](https://github.com/Hackerly0) & [@salshaha](https://github.com/salshaha)

---

## Gameplay Loop

- Explore the maze in classic Wolf3D style.
- When you **open a door**:
  1) You get a **random question**.  
  2) If you miss it, you get **another random question**.  
  3) Miss again → **scary face** and game over.
- Win condition: **Open all doors**.

### Default Controls (typical Cub3D)
- **W / A / S / D** — move
- **← / →** — rotate view
- **SPACE** — interact / open door (triggers the question)
- **ESC** — quit

> Tip: Some maps contain “void pockets” that are intentionally unreachable and should still pass validation.

---

## Quick Start

```bash
# 1) Clone
git clone https://github.com/Hackerly0/cub3d-door.git
cd cub3d-door

# 2) Build
make          # builds ./cub3D

# 3) Run the main map
./cub3D maps/door.cub

# 4) Try other maps (feel free to explore)
./cub3D maps/<any-map>.cub
```

- The primary map is **`maps/door.cub`**.  
- There are **plenty of other maps** in `maps/` for testing edge cases and validation.

---

## Requirements

- **make** and **gcc/clang**
- **MiniLibX** (bundled or fetched by the Makefile)
- **Dependencies** (already linked through `MLXFLAGS` in the Makefile):
  ```bash
  MLXFLAGS = -Iinclude -ldl -lglfw -pthread -lm
  ```
  These flags indicate the required system libraries:
  - `-ldl` — dynamic linking library  
  - `-lglfw` — GLFW (used by MiniLibX for window management & OpenGL context)  
  - `-pthread` — POSIX threads for concurrency  
  - `-lm` — math library  

### Linux (Debian/Ubuntu)
You can install everything needed via:
```bash
sudo apt-get update
sudo apt-get install -y build-essential libglfw3-dev libx11-dev libxext-dev libbsd-dev
```

### macOS
MiniLibX uses AppKit & OpenGL natively; you usually **don’t need extra installs** on 42 iMacs or macOS setups.

> 💡 If you face linking errors, check your GLFW installation or re-run `make re` after cleaning.

---

## Project Structure (common layout)

```
.
├── Makefile
├── cub3D                 # built binary
├── include/              # headers
├── src/                  # game sources (parser, raycaster, input, door logic, Q&A)
├── libmlx/               # MiniLibX (if vendored)
├── assets/               # textures / images (includes scary face)
└── maps/
    ├── door.cub          # main map
    └── ...               # additional maps for testing
```

---

## Maps

- **Format**: Standard `.cub` with textures, colors, and a **closed map** of `1`s and `0`s.
- **Doors**: Placed in the layout—interact with **SPACE** to trigger Q&A.
- **Validation**: Inaccessible voids fully enclosed by walls are permitted; playable area must be sealed.

---

## Troubleshooting

- **Black window / nothing renders**  
  Ensure textures exist at the paths specified in the `.cub` file.
- **Window fails to open on Linux**  
  Check X11 dependencies and run inside an X session (not pure TTY).
- **Makefile issues**  
  Try `make re`. If MiniLibX isn’t detected, verify the path or install system libs.
- **Crashes when interacting**  
  Avoid pressing movement keys while the **question prompt** is active. (We guard for this, but aggressive input can still race on some setups.)

---

## Development Notes

- Door interaction freezes the render loop while a question is asked (two attempts max).
- Second attempt uses a **different** random question.
- Failure shows a **scary texture**/image for ~5 seconds before exiting.
- Designed to be compatible with 42’s **Cub3D** norms and MiniLibX.

---

## Roadmap / Ideas

- In-window UI for questions (no terminal I/O).
- Question packs / categories.
- Time-limited answers.
- Scoreboard and speed-run mode.

---

## Credits

- **Core & Gameplay**: [@Hackerly0](https://github.com/Hackerly0)  
- **Teammate**: [@salshaha](https://github.com/salshaha)  
- **MiniLibX**: © 42

---

### Have fun opening doors… and answering wisely 😈
