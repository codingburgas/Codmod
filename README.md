[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/TH5oISMB)

# Contact Management System

A menu-driven C++20 desktop application for managing a personal contact
list. Contacts are stored on disk as JSON. The interface is built with
Dear ImGui. The code follows a **three-tier architecture** as required by
the project specification: presentation / logic / data, each split into
its own header and source file.

Runs on **Linux, macOS, and Windows** from the same CMake build.

## Features

- Add, edit, and delete contacts (first name, last name, phone, email).
- **Sort** the list by name or by phone number (Quick Sort).
- **Search** by first or last name (linear search, case-insensitive).
- Binary search by contact id over the sorted-by-id list.
- **Recursion demo**: total count of records + count of contacts whose
  phone number starts with a given prefix, both computed recursively.
- Persistent storage to a pretty-printed JSON file via `nlohmann::json`.
- Input validation with human-readable error messages in a status bar.

## Architecture

```
 Presentation (GUI) ────▶ Logic (algorithms, validation) ────▶ Data (JSON I/O)
    presentation.*              logic.*                          data.*
```

- `include/presentation.h` + `src/presentation.cpp` — Dear ImGui widgets,
  table, add/edit form, toolbar. **Only** calls the logic layer.
- `include/logic.h` + `src/logic.cpp` — Quick Sort, linear and binary
  search, recursive counting, CRUD, and validation. Calls the data layer.
- `include/data.h` + `src/data.cpp` — Defines the `Contact` struct and
  reads/writes the JSON file. The only layer that touches the file
  system.
- `src/main.cpp` — Boots GLFW + OpenGL + Dear ImGui and drives the frame
  loop; delegates all UI rendering to the presentation layer.

Per the specification, the presentation layer never calls the data layer
directly — all access goes through the logic layer.

## Orchestration & Windowing

Beyond the three-tier architecture, two additional files handle the application's
lifecycle and rendering loop:

- `main.cpp` — Entry point that parses command-line arguments and delegates to
  `runApplication()`.
- `application.cpp` — Orchestrates the application lifecycle: resolves the data
  file path, initializes the window via GLFW, loads contacts into the GUI state,
  runs the main loop, persists contacts back to disk, and cleans up resources.
- `glfw.cpp` — Encapsulates all GLFW, OpenGL, and Dear ImGui initialization and
  the main rendering loop. Creates the window, sets up the OpenGL 3.0 context,
  initializes ImGui backends, and repeatedly polls events, renders the frame
  callback, and swaps buffers until the window closes.

## Project layout

```
project-root/
├── include/                  # Public headers, one per layer
│   ├── data.h
│   ├── logic.h
│   ├── presentation.h
│   ├── application.h         # Orchestration & lifecycle management
│   └── glfw.h                # GLFW/OpenGL/ImGui windowing & rendering
├── src/                      # Implementations
│   ├── main.cpp              # Entry point; initializes and runs the application
│   ├── application.cpp       # Orchestrates lifecycle: window, data, main loop, persistence
│   ├── glfw.cpp              # Manages GLFW/OpenGL/ImGui initialization and frame loop
│   ├── presentation.cpp
│   ├── logic.cpp
│   └── data.cpp
├── data/
│   └── contacts.json         # Sample data file
├── external/                 # Third-party sources
│   ├── json/json.hpp           # nlohmann::json single header (vendored)
│   ├── imgui/                  # Dear ImGui (git submodule)
│   └── glfw/                   # GLFW (git submodule)
├── docs/                     # Sprint plans, architecture diagrams
├── assets/                   # Images / screenshots
├── CMakeLists.txt
└── README.md
```

## Prerequisites

- A C++20-capable compiler
  (GCC 11+, Clang 13+, Apple Clang 14+, or MSVC 19.29+).
- CMake 3.15 or newer.
- An OpenGL-capable graphics driver (standard on any modern desktop).
- On Linux: X11 / Wayland and `xkbcommon` development headers (needed by
  GLFW when it is built from source). On Debian/Ubuntu:
  `sudo apt install libx11-dev libxkbcommon-dev libwayland-dev`.

GLFW and Dear ImGui are pulled in as git submodules under `external/` and
built from source — no system-wide install of either is required.

## Build and run

First-time clone — pull the submodules:

```bash
git clone --recurse-submodules <repo-url>
# or, if you already cloned without --recurse-submodules:
git submodule update --init --recursive
```

### Linux / macOS

```bash
cmake -S . -B build
cmake --build build --parallel

./build/bin/contact_management_system
# or point it at a custom data file:
./build/bin/contact_management_system path/to/my_contacts.json
```

### Windows (PowerShell)

```powershell
cmake -S . -B build
cmake --build build --config Release --parallel

.\build\bin\Release\contact_management_system.exe
```

The CMake build copies `data/contacts.json` next to the executable after
every build, so launching from either the project root or the binary's
folder works.

## Data file format

```json
[
    {
        "contactId": 1,
        "firstName": "Ada",
        "lastName": "Lovelace",
        "phoneNumber": "+359888123456",
        "emailAddress": "ada@example.com"
    }
]
```

## Coding conventions

The source follows the style rules stated in the project specification:

- Structured programming (no OOP) — plain `struct`s and free functions.
- Four-space indentation, lines capped at ~100 characters.
- `lowerCamelCase` for variables, verb-initial `lowerCamelCase` for
  functions, `UPPER_SNAKE_CASE` for named constants.
- Every header opens with a block comment describing its purpose; every
  non-trivial function has a short comment describing what it does.
- `#pragma once` in every header; STL containers (`std::vector`,
  `std::string`) preferred over raw arrays.

## Team

| Profile Picture | Name | GitHub |
|---|---|---|
| ![Vladimir Kosev](assets/MrKokosev.jpg) | [Vladimir Kosev](https://github.com/vikosev24) | [github.com/vikosev24](https://github.com/vikosev24) |
| ![Olexandra Kikavsyka](assets/MsKikavsyka.jpg) | [Olexandra Kikavsyka](https://github.com/OOKikavska24) | [github.com/OOKikavska24](https://github.com/OOKikavska24) |
| ![Beray Nuri](assets/MrNuri.png) | [Beray Nuri](https://github.com/BGNuri24) | [github.com/BGNuri24](https://github.com/BGNuri24) |
