//
// Created by Mert Şerafettin Kargı on 6.01.2024.
//

#include "dijktras.h"
#include <iostream>
#include <string>

using namespace std;

/*
int shortPath[V];

void printPath(int path[], int i)
{
    // Base Case.
    if (path[i]==-1)
        return;

    printPath(path, path[i]);

    printf("%d ", i+1);
}
*/

int minDistance(int dist[], bool known[]){
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (known[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void bubbleSort(int arr[], int n, int cityPlates[81]) {
    for (int i = 0; i < 81; i++)
        cityPlates[i] = i + 1;
    int i, j;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swap(cityPlates[j], cityPlates[j + 1]);
            }
        }
    }
    //printArray(arr, n);
    //printArray(cityPlates, 81);
}



void printSolution(int dist[], Graph& graphObj, int dest = 1,int kClosest = 1){

    Node* tempNode = graphObj.LL.getNode(dest+1);
    int cityPlates[81], currentCity;

    if(kClosest == 1) {
        cout << tempNode->name << "\t----" << dist[dest] << "Km" << endl;
        //printPath(shortPath, dest-1);
       // for(int i = 0; i < )
        return; }
    bubbleSort(dist, 81, cityPlates);

    //cout << tempNode->name;
    //printArray(cityPlates, 81);
    for(int i = 0; i < kClosest; i++){
        currentCity = cityPlates[i+1];
        tempNode = graphObj.LL.getNode(currentCity);
        cout << tempNode->name << "\t----" << dist[i+1] << "Km" << endl;
    }
}

void dijkstra(Graph& graphObj, int src, int dest, int kClosest = 1)
{
    src--, dest--;
    //shortPath[src] = -1; // SOURCE'S PATH.
    int graph[V][V], i , j;
    for( i = 0; i < 81; i++){
        for(j = 0; j < 81; j++){
            graph[i][j] = 0;
        }
    }
    Node *tempNode1 = graphObj.LL.head->nextCity;
    Node* tempNode2;
    while(tempNode1 != nullptr){
        tempNode2 = tempNode1->adjCity;
        while( tempNode2 != nullptr ){
            graph[ tempNode1->plate - 1][tempNode2->plate - 1] = tempNode2->weight;
            tempNode2 = tempNode2->adjCity;
        }
        tempNode1 = tempNode1->nextCity;
    }

    int dist[V];
    bool sptSet[V];
    int tempCount = 1;
    for (i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[src] = 0;
                                                // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                //shortPath[v] = u;   // STORING THE PATH INDEXES.
                dist[v] = dist[u] + graph[u][v];
            }
    }
    Node* tempNode = graphObj.LL.getNode(src+1);
    cout << "From\t" << tempNode->name << "\tto:" << endl;
    printSolution(dist, graphObj, dest, kClosest);
}