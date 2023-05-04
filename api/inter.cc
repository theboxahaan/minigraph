#include<iostream>
#include<vector>

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



int main() {
    std::string source = "MartinJischke Drive";
    std::string dest = "DavidRoss Road";

    std::vector<Edge> sn = name_sssp(source, dest);
    std::cout<<"Dijkstra"<<std::endl;

    for(auto &e : sn) {
        std::cout<<e.tid<<" ";
    }
    std::cout<<std::endl;

    std::cout<<"name_KNN"<<std::endl;

    std::vector<std::vector<Edge>> eds = name_KNN(source, "university", 10);

    int i=0;
    for(auto &vs : eds) {
        std::cout<<i++<<std::endl;
        for(auto &v : vs) {
            std::cout<<v.tid<<" ";
        }
        std::cout<<std::endl;
    }

    std::cout<<"name_range"<<std::endl;

    eds = name_range(source, "university", 250);

    i=0;
    for(auto &vs : eds) {
        std::cout<<i++<<std::endl;
        for(auto &v : vs) {
            std::cout<<v.tid<<" ";
        }
        std::cout<<std::endl;
    }
    return 0;
}