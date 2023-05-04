#include<string>
#include<vector>
#include<utility>
#include<unordered_set>
#include<unordered_map>
#include<set>

#include<random>
#include<iostream>
#include<list>

#ifndef HEADER_H
#define HEADER_H
#include "../include/edge.h"
#endif



std::vector<Edge> consPath(std::unordered_map<Edge, Edge, EdgeHash> &cameFrom, Edge &ed, int dist) {
    std::vector<Edge> ans;
    Edge cur = ed;

    while (cameFrom.find(cur) != cameFrom.end()) {
        ans.push_back(cur);
        cur = cameFrom[cur];
    }
    ans.push_back(cur);
    ans.push_back(Edge(dist, 0, "", ""));
    std::reverse(ans.begin(), ans.end());
    return ans;
}


std::vector<Edge> dijs(int stid, int dtid) {

    std::unordered_map<int, int> offs = prepOffset();
    std::ifstream file(tidFile);

    std::vector<Edge> ans;

    std::set<std::pair<double, Edge>> openList;
    std::set<Edge> closedList;
    std::unordered_map<Edge, double, EdgeHash> dist;
    std::unordered_map<Edge, Edge, EdgeHash> cameFrom;

    Edge start = getEdge(offs, file, stid);
    Edge end = getEdge(offs, file, dtid);

    openList.insert({0, start});
    dist[start] = 0;
    
    while(!openList.empty()) {
        std::pair<double, Edge> p = *(openList.begin());
        openList.erase(openList.begin());

        Edge u = p.second;
        if(u.tid == dtid) {
            if(file.is_open()) file.close();
            return consPath(cameFrom, u, dist[u]);
        }
        for(auto &vtid : u.neighbours) {
            Edge v = getEdge(offs, file, vtid);
            if(closedList.find(u) != closedList.end()) continue;

            if(dist.find(v) == dist.end()) {
                dist[v] = dist[u] + v.length;
                openList.insert({dist[v], v});
                cameFrom[v] = u;

            } else if(dist[v] > dist[u] + v.length) {
                openList.erase(openList.find({dist[v], v}));
                dist[v] = dist[u] + v.length;
                openList.insert({dist[v], v});
                cameFrom[v] = u;
            }
        }
        closedList.insert(u);
    }
    if(file.is_open()) file.close();
    return ans;
}

std::vector<std::vector<Edge>> range(int stid, int range, std::string type) {
    std::unordered_map<int, int> offs = prepOffset();
    std::ifstream file(tidFile);

    std::vector<std::vector<Edge>> ans;

    std::set<std::pair<double, Edge>> openList;
    std::set<Edge> closedList;
    std::unordered_map<Edge, double, EdgeHash> dist;
    std::unordered_map<Edge, Edge, EdgeHash> cameFrom;

    Edge start = getEdge(offs, file, stid);

    openList.insert({0, start});
    dist[start] = 0;
    
    while(!openList.empty()) {
        std::pair<double, Edge> p = *(openList.begin());
        openList.erase(openList.begin());

        Edge u = p.second;
        if(u.type == type) {
            ans.push_back(consPath(cameFrom, u, dist[u]));
            continue;
        }
        if(dist[u] > range) continue;
        
        for(auto &vtid : u.neighbours) {
            Edge v = getEdge(offs, file, vtid);
            if(closedList.find(u) != closedList.end()) continue;

            if(dist.find(v) == dist.end()) {
                dist[v] = dist[u] + v.length;
                openList.insert({dist[v], v});
                cameFrom[v] = u;

            } else if(dist[v] > dist[u] + v.length) {
                openList.erase(openList.find({dist[v], v}));
                dist[v] = dist[u] + v.length;
                openList.insert({dist[v], v});
                cameFrom[v] = u;
            }
        }
        closedList.insert(u);
    }
    if(file.is_open()) file.close();
    return ans;
}

std::vector<std::vector<Edge>> KNN(int stid, int nreq, std::string type) {

    std::unordered_map<int, int> offs = prepOffset();
    std::ifstream file(tidFile);

    std::vector<std::vector<Edge>> ans;

    std::set<std::pair<double, Edge>> openList;
    std::set<Edge> closedList;
    std::unordered_map<Edge, double, EdgeHash> dist;
    std::unordered_map<Edge, Edge, EdgeHash> cameFrom;

    Edge start = getEdge(offs, file, stid);

    openList.insert({0, start});
    dist[start] = 0;
    
    while(!openList.empty() && nreq > 0) {
        std::pair<double, Edge> p = *(openList.begin());
        openList.erase(openList.begin());

        Edge u = p.second;
        if(u.type == type) {
            ans.push_back(consPath(cameFrom, u, dist[u]));
            nreq--;
            continue;
        }
        for(auto &vtid : u.neighbours) {
            Edge v = getEdge(offs, file, vtid);
            if(closedList.find(u) != closedList.end()) continue;

            if(dist.find(v) == dist.end()) {
                dist[v] = dist[u] + v.length;
                openList.insert({dist[v], v});
                cameFrom[v] = u;

            } else if(dist[v] > dist[u] + v.length) {
                openList.erase(openList.find({dist[v], v}));
                dist[v] = dist[u] + v.length;
                openList.insert({dist[v], v});
                cameFrom[v] = u;
            }
        }
        closedList.insert(u);
    }
    if(file.is_open()) file.close();
    return ans;
}


// int main() {

//     // Edge e = readEdgeFromFile(17);

//     // std::cout<<e.length<<std::endl;

//     std::vector<Edge> sn = dijs(1, 328);
//     std::cout<<"Dijkstra"<<std::endl;

//     for(auto &e : sn) {
//         std::cout<<e.tid<<" ";
//     }
//     std::cout<<std::endl;

//     int knn = 10;
//     int rn = 200;

//     std::cout<<"KNN"<<std::endl;

//     std::vector<std::vector<Edge>> eds = KNN(112, knn, "university");

//     int i=0;
//     for(auto &vs : eds) {
//         std::cout<<i++<<std::endl;
//         for(auto &v : vs) {
//             std::cout<<v.tid<<" ";
//         }
//         std::cout<<std::endl;
//     }

//     std::cout<<"Range"<<std::endl;

//     eds = range(112, rn, "university");

//     i = 0;
//     for(auto &vs : eds) {
//         std::cout<<i++<<std::endl;
//         for(auto &v : vs) {
//             std::cout<<v.tid<<" ";
//         }
//         std::cout<<std::endl;
//     }

// }