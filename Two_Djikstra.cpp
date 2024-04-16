//
// Created by misfi on 4/15/2024.
//

#include <algorithm>
#include "Graph.h"
#include "Edge.h"
#include "Airport.h"
#include "MinHeap.h"


std::vector<Edge> shortest_path(Graph graph, Airport origin, Airport destination){
    MinHeap prioQueue;

    int size = graph.connections.size();
    int originIndex = origin.index;
    int destIndex = destination.index;

    std::vector<double> dist(size, INT_MAX); // holds shortest distance from source to index[i] node
    std::vector<int> prev(size, -1); // holds the index of the previous node

    dist[originIndex] = 0;
    int min = INT_MAX;
    std::vector<Edge> curr = graph.connections[originIndex];

    for(int i = 0; i < curr.size(); i++){
        prioQueue.insert(curr[i]);
    }

    while(prioQueue.size > 0){
        Edge minEdge = prioQueue.popMin();
        if(destination.airportInitials == minEdge.destination.airportInitials){
            break;
        }
        int minIndex = minEdge.destination.index;

        std::vector<Edge> neighbor = graph.connections[minIndex];

        for(int i = 0; i < neighbor.size(); i++){
            double distance = neighbor[i].distance;
            int edgeIndex = neighbor[i].destination.index;

            if(dist[minIndex] != INT_MAX && dist[minIndex] + distance < dist[edgeIndex]){
                dist[edgeIndex] = dist[minIndex] + distance;
                prev[edgeIndex] = minIndex;
                prioQueue.insert(neighbor[i]);
            }
        }
    }

    std::vector<Edge> path;
    int cur = destIndex;

    while (prev[cur] != -1) {
        int parentIndex = prev[cur];
        path.push_back(graph.findConnection(parentIndex, cur));
        cur = parentIndex;
    }

    std::reverse(path.begin(), path.end());

    return path;
}

void printShortestPath(Graph g, Airport origin, Airport destination) {
    std::cout << "SHORTEST PATH: ";

    std::vector<Edge> shortpath = shortest_path(g, origin, destination);

    std::cout << origin.airportInitials;
    for (int i = 0; i < shortpath.size(); i++) {
        std::cout << "->" << shortpath[i].destination.airportInitials;
    }
    std::cout << '\n';
}







//Edge minEdge(std::vector<double> distance, std::vector<Edge> edges) {
//    Edge min = edges[0];
//
//    for (int i = 1; i < edges.size(); i++) {
//        int edgeInd = edges[i].destination.index;
//        int minInd = min.destination.index;
//
//        if (distance[edgeInd] < distance[minInd]) {
//            min = edges[i];
//        }
//    }
//
//    return min;
//}
//
//
//std::vector<Edge> shortest_path(Graph graph, Airport source, Airport destination){
//    int destIndex = graph.findAirport(destination.airportInitials);
//
//    std::vector<double> distance;
//    std::vector<bool> visited;
//
//    MinHeap heap;
//
//    for(int i = 0; i < graph.airports.size(); i++){
//        distance.push_back(INT_MAX);
//        visited.push_back(false);
//    }
//
//    int index = graph.findAirport(source.airportInitials);
//    int numVisited = 0;
//    distance[index] = 0;
//
//    while(numVisited < visited.size()){
//        for(int i = 0; i < graph.connections[index].size(); i++) {
//            Edge neighborEdge = graph.connections[index][i];
//            int currNeighbor = neighborEdge.destination.index;
//
//            if (visited[currNeighbor]) {
//                continue;
//            }
//
//            heap.insert(neighborEdge);
//            double distanceToNeighbor = distance[index] + neighborEdge.distance;
//            if (distance[currNeighbor] > distanceToNeighbor) {
//                distance[currNeighbor] = distanceToNeighbor;
//            }
//        }
//
//        visited[index] = true;
//        numVisited++;
//        try {
//            index = heap.popMin().destination.index;
//        }
//        catch(std::string e) {
//            std::cout << e << '\n';
//        }
//
////        if(graph.airports[index].airportInitials == destination.airportInitials){
////            break;
////        }
//    }
//
//    if (distance[destIndex] == INT_MAX) return std::vector<Edge>(0);
//
//    std::vector<Edge> path;
//    index = source.index;
//
////    while (graph.airports[index].airportInitials != destination.airportInitials) {
////        Edge minimum = minEdge(distance, graph.connections[index]);
////
////        path.push_back(minimum);
////        index = minimum.destination.index;
////    }
//
//    return path;
//}



