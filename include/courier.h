#ifndef COURIER_H
#define COURIER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Konstansok, Alapérték beállitása demo teszt esethez //
#define MAX_LOCATION 100
#define MAX_NAME_LEN 64
#define INF INT_MAX
#define MAX_STOPS 50

// --- Adatszerkezetek --- //
typedef struct {
    int dest_vertex;
    int distance_weight;
    struct Node *next;
} AdjNode; //Gráf csúcsai és élei

typedef struct {
    int locations;
    char name[MAX_LOCATION][MAX_NAME_LEN];
    Node *adj[MAX_LOCATION];
} Graph; //Gráf - Éllista reprezentációja

typedef struct {
    int vertex;
    int distance;
} HeapNode; //Mininális bináris kupac elemei

typedef struct {
    int size;
    int capacity;
    HeapNode *data;
} MinHeap; //Minimális bináris kupac, priority queue-hoz

typedef struct {
    int location_id;
    int priority; /* Minél alacsonyabb érték annál magassab prioritás */
    char label[MAX_NAME_LEN];
} DeliveryStop; //Szállitási cim prioritással

typedef struct {
    DeliveryStop stops[MAX_STOPS];
    int count;
} DeliveryQueue; //Szállitási cimek prioritási sorrendben

typedef struct {
    int dist[MAX_LOCATION]; //Legrövidebb út
    int prev[MAX_LOCATION]; //Elért csúcs
} DijkstraResult;



#endif
