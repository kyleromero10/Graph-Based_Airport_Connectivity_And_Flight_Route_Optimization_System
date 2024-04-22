#pragma once

#include <climits>
#include <string>
#include <vector>
#include <iostream>

#include "Edge.h"
#include "Graph.h"

/*
* Min heap used to store edges based on a certain weight
* (either weight or cost)
*/
class MinHeap {
public:
  std::vector<Edge> arr; // init to size 1 to make everything easier (children being 2i and 2i + 1 instead of 2i + 1 and 2i + 2)
  int size = 0;

  bool useCostToCompare = false; // Do determine if our comparisons use cost instead of distance

  MinHeap() { arr.push_back(Edge()); }
  MinHeap(bool useCostToCompare) : useCostToCompare(useCostToCompare){ arr.push_back(Edge()); }

  MinHeap(const Graph& graph) {
    std::vector<std::vector<Edge>> connections = graph.connections;

    arr.push_back(Edge());

    for (int i = 0; i < connections.size(); i++) {
      for (int j = 0; j < connections[i].size(); j++) {
        arr.push_back(connections[i][j]);
        size++;
      }
    }

    heapify();
  }
  
  // Heapify an array
  void heapify() {
    for (int i = size / 2; i > 0; i--)
      percolateDown(i);
  }
  
  // To handle comparisons between edges
  // returns positive integer if e1 > e2 negative if e1 < e2 and 0 if equal
  int compare(const Edge& e1, const Edge& e2) {
    if (useCostToCompare) {
      return e1.cost - e2.cost;
    }

    return e1.distance - e2.distance;
  }
  
  // Returns the index with the minimum value (whether it is cost or distance)
  int minIndex(int ind1, int ind2) {
    // If one index is out of bounds return the other, if they both are return -1
    if (ind1 >= size && ind2 >= size) {
      return -1;
    }
    // ind1 is in bounds
    else if (ind2 > size) {
      return ind1;
    }
    // ind2 is in bounds
    else if (ind1 > size) {
      return ind2;
    }

    int comparison = compare(arr[ind1], arr[ind2]);

    if (comparison < 0) {
      return ind1;
    }
    
    return ind2;
  }
  
  // swaps two indexes within the array
  void swap(int i, int j) {
    Edge temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }

  // inserts item into MinHeap
  void insert(const Edge& toInsert) {
    arr.push_back(toInsert);
    size++;
    percolateUp(size);
  }

  // Deletes and returns the top element (the min)
  Edge popMin() {
    if (size <= 0) {
      throw std::string("Heap is empty cannot pop");
    }
    
    Edge toReturn = arr[1];
    arr[1] = arr[size]; // index 1 is top
  
    arr.pop_back();
    size--;
    percolateDown(1);

    return toReturn;
  }
  
  // When inserting a new element, it starts at the bottom and we need to make sure it's smaller than all of its parents
  void percolateUp(int index) {
    if (index <= 1) return;
    
    int parentIndex = index / 2;
    int minInd = minIndex(index, parentIndex);

    // arr[index] < arr[parentIndex] 
    if (minInd != index) {
      swap(index, parentIndex);
      percolateUp(parentIndex);
    }
  }
  
  // When deleting the top node we need all elements
  void percolateDown(int index) {
    int leftChild = 2*index, rightChild = 2*index + 1;
    
    int minimum = minIndex(leftChild, rightChild);
    
    if (minimum == -1) return; // out of bounds
    
    // Element is not the min of its subtree so we percolate down again
    if (compare(arr[index], arr[minimum]) > 0) {
      swap(index, minimum);
      percolateDown(minimum);
    }
  }

  void print() {
    std::cout << "{ ";

    for (int i = 0; i < arr.size(); i++) {
      std::cout << arr[i].distance << " "; 
    }

    std::cout << " }\n";
  }
};
