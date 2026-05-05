#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include "heap.h"

// --- Adatszerkezetek --- //
typedef struct
{
    int dist[MAX_LOCATION]; /* Legrövidebb út */
    int prev[MAX_LOCATION]; /* Ezzel elért csúcs */
} DijkstraResult;           // Dijkstra eredménye

// --- Függvénydeklarációk --- //
DijkstraResult dijkstra(const Graph *g, int src);
void print_path(const DijkstraResult *r, const Graph *g, int src, int dest);

#endif
