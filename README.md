<p align="center">
  <h1 align="center">🗺️ Route Planning & Delivery System</h1>
  <p align="center"><em>Shortest-path route planner with priority-based delivery scheduling — written in C</em></p>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/language-C11-555555?style=for-the-badge&logo=c" alt="C11">
  <img src="https://img.shields.io/badge/build-CMake-064F8C?style=for-the-badge&logo=cmake" alt="CMake">
  <img src="https://img.shields.io/badge/BME-VIHIAV10-8B0015?style=for-the-badge" alt="BME VIHIAV10">
</p>

---

## 📋 Table of Contents

- [About](#about)
- [Algorithms & Data Structures](#algorithms--data-structures)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Build](#build)
  - [Run](#run)
- [Usage Guide](#usage-guide)
  - [1. Map Management](#1-map-management)
  - [2. Route Finding](#2-route-finding)
  - [3. Delivery Scheduling](#3-delivery-scheduling)
  - [4. File I/O](#4-file-io)
- [Delivery Route Logic](#delivery-route-logic)
- [File Format](#file-format)
- [Design Rationale](#design-rationale)
- [Course Context](#course-context)

---

## About

This is the **mandatory major assignment** for the course *Algorithms, Data Structures and their Efficient Implementation in C Language* at **Budapest University of Technology and Economics (BME)**, Faculty of Electrical Engineering and Informatics.

The task: build a real-world application in C that demonstrates non-trivial algorithms and data structures covered in the course. This project solves a **logistics / last-mile delivery routing problem** — given a map of locations connected by roads of varying distances, and a queue of delivery stops with different priorities, the system computes optimal shortest-path routes to visit all stops in priority order and return to base.

---

## Algorithms & Data Structures

| Data Structure | Concrete Implementation | Algorithmic Role |
|:---|:---|:---|
| **Graph** | Undirected weighted graph via adjacency list (dynamically allocated linked-list edges) | Models locations as vertices and road segments as edges for shortest-path queries |
| **Min-Heap (Priority Queue)** | Array-based binary min-heap with automatic capacity doubling; `sift_up` / `sift_down` | Extracts the closest unvisited vertex in *O*(log *V*) during Dijkstra's algorithm |
| **Dijkstra's Algorithm** | Single-source shortest path for non-negative edge weights | Computes optimal point-to-point and one-to-all shortest routes |
| **Delivery Queue** | Insertion-sorted array ordered by priority field | Ensures higher-priority stops are always visited first |

### Computational Complexity

| Operation | Time |
|:---|:---|
| Dijkstra (full run) | *O*((*V* + *E*) log *V*) |
| Heap `push` / `pop` | *O*(log *n*) |
| Delivery insertion | *O*(*n*) insertion sort per add |
| Graph add/remove vertex | *O*(*V* + *E*) |
| Graph add/remove edge | *O*(1) amortized |

---

## Project Structure

```
.
├── CMakeLists.txt              # CMake build config (C11, Debug profile)
├── include/
│   ├── macro.h                 # Shared constants, limits, standard headers
│   ├── graph.h                 # Graph & adjacency-node type definitions
│   ├── heap.h                  # MinHeap & HeapNode type definitions
│   ├── dijkstra.h              # DijkstraResult type & API
│   └── delivery.h              # DeliveryStop & DeliveryQueue types
├── src/
│   ├── main.c                  # Entry point, CLI menus, file save/load
│   ├── graph.c                 # Graph: create, add/remove vertex & edge, print
│   ├── heap.c                  # MinHeap: create, push, pop, sift-up, sift-down
│   ├── dijkstra.c              # Dijkstra's shortest path & path reconstruction
│   └── delivery.c              # Delivery queue CRUD, sorting, route generation
├── bin/                        # Compiled binary output (CourierRoutingSystem)
└── README.md
```

---

## Getting Started

### Prerequisites

- **CMake** ≥ 3.10
- **GCC** or **Clang** with C11 support
- Linux / macOS / WSL (or any POSIX environment)

### Build

```bash
cmake -B build
cmake --build build
```

The executable is written to `bin/CourierRoutingSystem`.

### Run

```bash
./bin/CourierRoutingSystem
```

You will be greeted by the main menu:

```
╔══════════════════════════════════════╗
║                                      ║
║    Útvonaltervező rendszer           ║
║    Kötelező nagy házi feladat | C    ║
║                                      ║
╚══════════════════════════════════════╝

╔═══ Fő menü ════╗
║ 1) Térkép        ║
║ 2) Útvonalak     ║
║ 3) Szállítások   ║
║ 4) Fájl I/O      ║
║ 0) Kilépés       ║
╚══════════════════╝
```

---

## Usage Guide

### 1. Map Management

> Add locations → connect them with weighted road segments → model your own delivery map.

| Action | Description |
|:---|:---|
| Add location | Assign a name; the system auto-generates a numeric ID |
| Remove location | Delete a vertex and all its incident edges; IDs are compacted |
| Add route | Create a bidirectional road with a distance weight (km) |
| Remove route | Delete the road segment between two locations |
| List locations | Display the adjacency list for the entire graph |

### 2. Route Finding

> Single shortest path or full distance matrix from any origin.

| Action | Description |
|:---|:---|
| Shortest path (A → B) | Print the exact vertex-by-vertex path and total distance |
| All paths from origin | Print shortest distances from one location to every other |

### 3. Delivery Scheduling

> Build a prioritized delivery queue, then generate an optimized multi-stop route.

| Action | Description |
|:---|:---|
| Add stop | Attach a location, priority, and customer label to the queue |
| Remove stop | Delete a stop by its queue index |
| List stops | Display all queued stops sorted by priority |
| Generate route | Compute the full delivery circuit starting from a chosen depot |

### 4. File I/O

> Persist your map to disk and reload it later.

| Action | Description |
|:---|:---|
| Save map | Write all locations and edges to a plain-text file |
| Load map | Restore a previously saved map, replacing the current one |

---

## Delivery Route Logic

When **"Generate route"** is selected, the system performs the following:

1. **Sort** the delivery queue by priority (lower number = more urgent).
2. **Start** from the user-chosen depot location.
3. For **each stop** in priority order:
   - Run **Dijkstra's algorithm** from the current position.
   - Trace the shortest path to the stop's location.
   - Record the distance and advance the current position.
4. After all stops are served, **return to the depot** via the shortest path.
5. Report **per-leg distances** and the **total circuit distance**.

---

## File Format

Maps are serialized as human-readable plain text:

```text
Helyszínek száma:<N>
 <id> <name>
 ...
Élek:
 <src> <dest> <weight>
 ...
Vége
```

- The parser skips blank lines and ignores trailing whitespace.
- Edges are undirected — each edge is stored once in the file but inserted in both directions at load time.
- The `Vége` sentinel marks end-of-file; anything after it is ignored.

---

## Design Rationale

| Decision | Why |
|:---|:---|
| **Adjacency list over matrix** | Sparse graphs (road networks) waste less memory; edge iteration during Dijkstra is proportional to degree, not total vertices |
| **Binary min-heap over Fibonacci heap** | Simpler to implement correctly; *O*(log *V*) per operation is sufficient for the assignment scale |
| **Undirected edges** | Roads are bidirectional by default; `graph_add_edge` inserts both `(u,v)` and `(v,u)` |
| **Vertex ID compaction on removal** | Keeps IDs 0..*N*−1 contiguous so arrays (`dist[]`, `prev[]`, `name[][]`) stay dense and index-based lookups remain trivial |
| **Dynamic heap capacity** | Avoids a fixed upper bound — the heap doubles on overflow, bounded only by available memory |
| **Insertion sort for delivery queue** | Small *n* (max 50 stops) makes *O*(*n*²) acceptable; keeps the code simple and the queue always sorted |

---

## Course Context

| | |
|:---|:---|
| **University** | Budapest University of Technology and Economics (BME) |
| **Faculty** | Faculty of Electrical Engineering and Informatics (VIK) |
| **Course code** | BMEVIHIAV10 |
| **Course title** | Algorithms, Data Structures and their Efficient Implementation in C Language |
| **Assignment** | Mandatory major project (kötelező nagy házi feladat) |
| **Language** | C11 |
| **Build system** | CMake |
