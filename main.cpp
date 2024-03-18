#include <iostream>
#include <string>
#include "Graph.h"
#include "dijktras.h"

using namespace std;

int main() {

    Graph graph("adjacent_cities.txt", "CityDistances1.txt");
    //dijkstra(graph, 6, 1, 1);
    Node* tempNode;
    char choiceMenu;
    string mainCity, selectdCity;
    int plateMainCity, plateSelectd;
    int tempNum;
    while(1){
        cout << "a. Enter City" << endl << "b. Print selected" << endl << "c. List k closest cities" << endl << "d. Find shortest path to" << endl << "x. exit" << endl;
        cout << "Choose one: ";
        cin >> choiceMenu;
        if(choiceMenu == 'a'){
            cout << "Enter city name: ";
            cin >> mainCity;
            plateMainCity = graph.LL.getNodePlate(mainCity);
            cout << "City is Selected." << endl;
        }
        else if(choiceMenu ==  'b') {
            tempNode = graph.LL.getNode(plateMainCity);
            cout << "Current city is: " << tempNode->name << " " << tempNode->plate << endl;
        }
        else if(choiceMenu == 'c'){
            cout << "Please enter number k: ";
            cin >> tempNum;
            dijkstra(graph, plateMainCity, 1, tempNum);
        }
        else if(choiceMenu == 'd'){
            cout << "Please enter city name to find path from " << mainCity << " :";
            cin >> selectdCity;
            plateSelectd = graph.LL.getNodePlate(selectdCity);
            dijkstra(graph,plateMainCity, plateSelectd, 1);
        }
        else if(choiceMenu == 'x')
            break;
    }
    return 0;
}
