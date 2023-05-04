#include<iostream>
#include<vector>
#include <chrono>


#ifndef HEADER_H
#define HEADER_H
#include "../include/edge.h"
#endif

#include "../src/hashIndex.cc"
#include "../src/dijkstra.cc"


std::vector<Edge> name_sssp(std::string source, std::string dest) {
    int sourceTid = search(source);
    int destinationTid = search(dest);
    return dijs(sourceTid, destinationTid);
}

std::vector<std::vector<Edge>> name_KNN(std::string source, std::string type, int count) {
    int sourceTid = search(source);
    return KNN(sourceTid, count, type);
}

std::vector<std::vector<Edge>> name_range(std::string source, std::string type, int distanceLimit) {
    int sourceTid = search(source);
    return range(sourceTid, distanceLimit, type);
}
