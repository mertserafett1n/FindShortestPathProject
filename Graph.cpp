//
// Created by Mert Şerafettin Kargı on 27.12.2023.
//

#include "Graph.h"
#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

Node::Node() {
    plate = 0;
    name = "Undefined";
    weight = 0;
    adjCity = nullptr;
    nextCity = nullptr;
}

Node::Node(std::string name, int plate, int weight) {
    this->name = name;
    this->plate = plate;
    this->weight = weight;
    nextCity = nullptr;
    adjCity = nullptr;
    //cout << "Node olusturuldu" << endl;
}


// ------------------------------------------------------------

LinkedList::LinkedList(){ head->nextCity = nullptr; head->adjCity = nullptr; }

Node* LinkedList::getNode(int plate) {
    Node* tmp = this->head->nextCity;
    while(tmp->plate!= plate)
        tmp = tmp->nextCity;
    //cout << "RETURNING NODE "<< tmp->name << " " << tmp->plate << endl;
    return tmp;
}

int LinkedList::getNodePlate(string name){
    Node *tmp = this->head->nextCity;
    while(tmp->name != name)
        tmp = tmp->nextCity;
    return tmp->plate;
}

void  LinkedList::connectNodes(Node*& x, Node*& y){ // x is the Main City, y is its neighbor.
    y->adjCity = x->adjCity;
    x->adjCity = y;
    //cout << head->nextCity->name << head->nextCity->adjCity->name << endl;
}

void LinkedList::insertNode(Node& x){
    if(head->nextCity == nullptr){
        head->nextCity = &x;
        return;
    }
    Node* temp = head;
    while(temp->nextCity != nullptr)
        temp = temp->nextCity;
    temp->nextCity = &x;
}

void LinkedList::insertNode(string name, int plate, int weight) {
    Node* newNode = new Node(name, plate, weight);
    insertNode(*newNode);
}


void LinkedList::printNextNodes(Node &x) {
    Node* temp = head->nextCity;
    int i = 1;
    while(temp->nextCity != nullptr){
        cout << i++ << "- "<< temp->name << endl;
        temp = temp->nextCity;
    }
}

void LinkedList::printAdjNodes(Node &x) {
    Node* temp = &x; // BURDA head->adjCity OLADABİLİR TEKRAR BAK.
    int i = 1;
    while(temp != nullptr){
        cout << i++ << "- "<< temp->name << temp->weight <<endl;
        temp = temp->adjCity;
    }
}

// ------------------------------------------------------------

Graph::Graph() { numOfVertex = 0; numOfEdge = 0; }

Graph::Graph(string fileName1, string fileName2){
    numOfVertex = 0, numOfEdge = 0;
    fstream readDistance;
    readDistance.open(fileName2, ios::in);
    if( !(readDistance.is_open()) ) { cout << "Read Distance file could not opened." << endl; return ;}

    string temp1;
    int i = 0, j;
    getline(readDistance, temp1);
    stringstream X(temp1);
    while(getline(X, labesOfNodes[i], ';')){i++;}
    labesOfNodes[80].erase(labesOfNodes[80].length()); //Getline reads new line character too????.

    string cityDistances[82][83];
    for(i = 0; i < 82;i++) {
        getline(readDistance, temp1, '\r');
        //temp1.erase(temp1.length()-1);
        //cout << temp1;
        j = 0;
        stringstream X(temp1);
        while(getline(X, cityDistances[i][j++], ';')) { }
        //cout << cityDistances[i][0] << cityDistances[i][1] <<cityDistances[i][j-2]; // Testing whether reading true or not.
    }
    readDistance.close();
    fstream readAdjCities;
    readAdjCities.open(fileName1, ios::in);
    if( !(readAdjCities.is_open()) ) { cout << "Adjacent Cities txt file could not opened." << endl; return;}

    string temp2, adjacentCities[81][10];
    int numOfAdjCities[81];
    for(i = 0; i < 81; i++){
        numOfAdjCities[i] = 0;
        getline(readAdjCities, temp2);
        //cout << temp2 << endl;
        stringstream X1(temp2);
        j = 0;
        while(getline(X1, adjacentCities[i][j], ',')){
            transform(adjacentCities[i][j].begin(), adjacentCities[i][j].end(), adjacentCities[i][j].begin(), ::tolower);
            j++;
        }
        numOfAdjCities[i] = j;
        // cout << adjacentCities[i][j-1] << endl;
    }
    readAdjCities.close();
    // Reading file is done!
    int k, distance;
    for(i = 0; i < 81; i++){
        Node* mainCity = new Node(adjacentCities[i][0], i+1, 0);
        LL.insertNode(*mainCity);
        for(j = 1; j < numOfAdjCities[i]; j++){
            k = 0;
            while(adjacentCities[i][j] != labesOfNodes[k]){
                k++;
            }
            distance = stoi(cityDistances[i][k+2]);
            Node* adjCity = new Node(adjacentCities[i][j], k+1, distance);
            //cout << adjCity->name << " " << adjCity->plate << " " << adjCity->weight << endl;
            addEdge(mainCity, adjCity);
        }
        //neighbors(*mainCity);
    }

}


Graph::Graph(int numberOfVertex) {
    numOfEdge = 0;
    this->numOfVertex = numberOfVertex;
    for(int i = 0; i < numberOfVertex; ++i)
        LL.insertNode("Undefined", 0, 0);
}

void Graph::adjacent(Node &x, Node &y) {
    Node* temp = &x;
    while(temp->adjCity != nullptr) {
        if(temp->adjCity->name == y.name){
            cout << "There is edge between " << x.name << " " << temp->adjCity->name << " With " << temp->adjCity->weight << " Cost" << endl;
            return;
        }
        temp = temp->adjCity;
    }
    cout << "There is not edge between " << x.name << " " << temp->adjCity->name << endl;
}

void Graph::neighbors(Node &x) { LL.printAdjNodes(x); }
void Graph::addVertex(Node &x) { LL.insertNode(x); numOfVertex++; }

void Graph::addEdge(Node*& x, Node*& y) {
    LL.connectNodes(x, y);
    numOfEdge++;
}