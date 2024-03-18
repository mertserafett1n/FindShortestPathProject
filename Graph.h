//
// Created by Mert Şerafettin Kargı on 27.12.2023.
//

#ifndef PROJECT2_GRAPH_H
#define PROJECT2_GRAPH_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Node {
public:
    string name;
    int plate, weight;
    Node* adjCity;
    Node* nextCity;

    Node();
    Node(string name, int plate, int weight);
};


class LinkedList{
public:
    Node* head;
    LinkedList();

    Node* getNode(int plate);
    int getNodePlate(string name);
    void connectNodes(Node*& x, Node*& y);
    void insertNode(string name, int plate, int weight);
    void insertNode(Node& x);
    void printAdjNodes(Node& x);
    void printNextNodes(Node& x);
};


class Graph{
    int numOfVertex;
    int numOfEdge;
    string labesOfNodes[81];
public:
    LinkedList LL;
    Graph();
    Graph(string fileName1, string fileName2);
    Graph(int numberOfVertex);

    void adjacent(Node&x, Node& y);
    void neighbors(Node& x);
    void addVertex(Node& x);
    void removeVertex(Node& x); // No Need to be Implemented
    void addEdge(Node*& x, Node*& y);
    int getVertexValue(Node &x);
    void setVertexValue(Node& x, int value);
    int getEdgeValue(Node& x, Node& y);
    void setEdgeValue(Node& x, Node& y, int weight);
    int getNumOfvertex() const{ return numOfVertex;}

};



#endif //PROJECT2_GRAPH_H
