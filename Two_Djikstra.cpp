//
// Created by misfi on 4/15/2024.
//

#include "Graph.h"
#include "Edge.h"
#include "Airport.h"
#include "MinHeap.h"


std::vector<Edge> shortest_path(Graph graph, Airport origin, Airport destination){



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



