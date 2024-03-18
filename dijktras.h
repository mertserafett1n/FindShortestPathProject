//
// Created by Mert Şerafettin Kargı on 6.01.2024.
//

#ifndef GRAPH_CPP_DIJKTRAS_H
#define GRAPH_CPP_DIJKTRAS_H

#include <iostream>
#include "Graph.h"
#include <climits>

using namespace std;
#define V 81

int minDistance(int dist[], bool known[]);
void dijkstra(Graph& graph, int src, int dest, int kClosest);
void printSolution(int dist[], Graph& graphObj, int dest,int kClosest);

#endif //GRAPH_CPP_DIJKTRAS_H
