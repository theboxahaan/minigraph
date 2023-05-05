// COMPILES W g++ -DDEBUG -std=c++14 inter.cc ../src/rtree.cc -I../

#include<iostream>
#include<vector>
#include <chrono>


#ifndef HEADER_H
#define HEADER_H
#include "../include/edge.h"
#endif

#include "../src/hashIndex.cc"
#include "../src/dijkstra.cc"
#include "../include/rtree.h"

std::vector<Edge> coordinate_sssp(std::array<std::pair<Dim, Dim>, 2> mbr_source, std::array<std::pair<Dim, Dim>, 2> mbr_dest) {
    auto rt  = Rtree(true);
    IdxEntryVectorD v_source, v_dest;
    db_in.seekg(0);
    
    rt.search_d(rt.root_d_[0].second, v_source, Rectangle(mbr_source));
    int sourceTid = v_source[0].second;
    for(auto x: v_source){
        // std::cout << "-> " << x.first[0].first << " " << x.first[0].second << " " << x.first[1].first << " " << x.first[1].second << " " << x.second <<  std::endl;
        if(x.second < sourceTid)
            sourceTid = x.second;
    }
    db_in.seekg(0);
    auto rt2 = Rtree(true);
    rt2.search_d(rt.root_d_[0].second, v_dest, Rectangle(mbr_dest));
    std::cout<<"d"<<" "<<v_dest.size()<<std::flush;
    int destinationTid = v_dest[0].second;
    for(auto x: v_dest){
        // std::cout << "-> " << x.first[0].first << " " << x.first[0].second << " " << x.first[1].first << " " << x.first[1].second << " " << x.second <<  std::endl;
        if(x.second < destinationTid)
            destinationTid = x.second;
    }
    std::cout<<std::endl<<sourceTid<<" "<<destinationTid<<std::flush;
    return dijs(sourceTid, destinationTid);
}


std::vector<std::vector<Edge>> coordinate_knn(std::array<std::pair<Dim, Dim>, 2> mbr_source, std::string type, int count) {
    db_in.seekg(0);
    
    auto rt  = Rtree(true);
    IdxEntryVectorD v_source;
    
    rt.search_d(rt.root_d_[0].second, v_source, Rectangle(mbr_source));
    int sourceTid = v_source[0].second;
    for(auto x: v_source){
        // std::cout << "-> " << x.first[0].first << " " << x.first[0].second << " " << x.first[1].first << " " << x.first[1].second << " " << x.second <<  std::endl;
        if(x.second < sourceTid)
            sourceTid = x.second;
    }
    
    return KNN(sourceTid, count, type);
}

std::vector<std::vector<Edge>> coordinate_name_range(std::array<std::pair<Dim, Dim>, 2> mbr_source, std::string type, int distanceLimit) {
    db_in.seekg(0);
    auto rt  = Rtree(true);
    IdxEntryVectorD v_source;
   
    
    rt.search_d(rt.root_d_[0].second, v_source, Rectangle(mbr_source));
    int sourceTid = v_source[0].second;
    for(auto x: v_source){
        // std::cout << "-> " << x.first[0].first << " " << x.first[0].second << " " << x.first[1].first << " " << x.first[1].second << " " << x.second <<  std::endl;
        if(x.second < sourceTid)
            sourceTid = x.second;
    }
    
   
    return range(sourceTid, distanceLimit, type);
}




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
    std::string source = "Dwight Way ";
    std::string dest = "Arden Road ";
    std::array<std::pair<Dim, Dim>, 2> mbr_source = {{{-122.2445702, -122.2443826}, {37.8590061 ,37.8598274 }}};
    std::array<std::pair<Dim, Dim>, 2> mbr_dest = {{{-122.2457593,-122.2444017},{37.8607704,37.8608807}}};
    // std::string source = "North Martin Jischke Drive ";
    // std::string dest = "Lawson Hall (LWSN) ";

    auto start = std::chrono::high_resolution_clock::now();
    // std::vector<Edge> sn = name_sssp(source, dest);
    std::vector<Edge> sn = coordinate_sssp(mbr_source, mbr_dest);
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout<<"Dijsktra: "<<duration.count()<<std::endl;



    for(auto &e : sn) {
        std::cout<<e.tid<<" ";
    }
    std::cout<<std::endl;


    start = std::chrono::high_resolution_clock::now();
    // std::vector<std::vector<Edge>> eds = name_KNN(source, "university", 10);
    std::vector<std::vector<Edge>> eds = coordinate_knn(mbr_source, "school", 10);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout<<"KNN: "<<duration.count()<<std::endl;


    int i=0;
    for(auto &vs : eds) {
        std::cout<<i++<<std::endl;
        for(auto &v : vs) {
            std::cout<<v.tid<<" ";
        }
        std::cout<<std::endl;
    }

    start = std::chrono::high_resolution_clock::now();

    // eds = name_range(source, "university", 5000);
    eds = coordinate_name_range(mbr_source, "school", 10000);

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout<<"range: "<<duration.count()<<std::endl;


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