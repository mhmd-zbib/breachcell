# BreachCell 2D Game Project

This is a simple C++ project structure for a 2D game using SDL and CMake (no engine).

## Folder Structure

- `src/` — Source files
- `include/` — Header files
- `assets/` — Game assets (images, sounds, etc.)
- `cmake/` — CMake modules/scripts
- `external/` — External libraries (e.g., SDL)
- `build/` — Build output
- `.github/` — Copilot instructions and workflows
- `.vscode/` — VSCode settings and tasks

## Build Instructions

1. Install SDL2 development libraries on your system.
2. Run CMake to configure the project:
   ```sh
   cmake -S . -B build
   cmake --build build
   ```
3. Run the game executable from the `build/` directory.

## Notes

- Place your C++ source files in `src/` and headers in `include/`.
- Place assets (images, sounds) in `assets/`.
- Add any additional CMake modules to `cmake/`.
- External libraries (like SDL) can be placed in `external/` if not installed system-wide.
