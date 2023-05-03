#include<string>
#include<vector>
#include<utility>
#include<unordered_set>
#include<unordered_map>
#include<set>

#include<random>
#include<iostream>
#include<list>

#include "../include/edge.h"



// class DNode {
//     public:
//     std::string name;
//     std::unordered_map<DNode*, double> neighs;
//     std::unordered_set<std::string> tags;
//     std::pair<double, double> loc;
// };


// std::unordered_map<DNode*, double> A_star(DNode *start, DNode *end, bool sssp) { 
//     std::set<std::pair<double, DNode*>> openList;
//     std::set<DNode*> closedList;
//     std::unordered_map<DNode*, double> dist;
//     std::unordered_map<DNode*, DNode*> cameFrom;

//     openList.insert({0, start});
//     dist[start] = 0;
    
//     while(!openList.empty()) {
//         std::pair<double, DNode*> p = *(openList.begin());
//         openList.erase(openList.begin());

//         DNode* u = p.second;
//         for(auto &v : u->neighs) {
//             if(closedList.find(u) != closedList.end()) continue;

//             if(dist.find(v.first) == dist.end()) {
//                 dist[v.first] = dist[u] + v.second;
//                 openList.insert({dist[v.first], v.first});
//                 cameFrom[v.first] = u;

//             } else if(dist[v.first] > dist[u] + v.second) {
//                 openList.erase(openList.find({dist[v.first], v.first}));
//                 dist[v.first] = dist[u] + v.second;
//                 openList.insert({dist[v.first], v.first});
//                 cameFrom[v.first] = u;
//             }

//         }
//         closedList.insert(u);
//     }
//     return dist;
// }

std::vector<Edge> consPath(std::unordered_map<Edge, Edge, EdgeHash> &cameFrom, Edge &ed) {
    std::vector<Edge> ans;
    Edge cur = ed;

    while (cameFrom.find(cur) != cameFrom.end()) {
        ans.push_back(cur);
        cur = cameFrom[cur];
    }
    ans.push_back(cur);
    std::reverse(ans.begin(), ans.end());
    return ans;
}


std::vector<Edge> dijs(int stid, int dtid) {
    std::vector<Edge> ans;

    std::set<std::pair<double, Edge>> openList;
    std::set<Edge> closedList;
    std::unordered_map<Edge, double, EdgeHash> dist;
    std::unordered_map<Edge, Edge, EdgeHash> cameFrom;

    Edge start = readEdgeFromFile(stid);
    Edge end = readEdgeFromFile(dtid);

    openList.insert({0, start});
    dist[start] = 0;
    
    while(!openList.empty()) {
        std::pair<double, Edge> p = *(openList.begin());
        openList.erase(openList.begin());

        Edge u = p.second;
        if(u.tid == dtid) {
            return consPath(cameFrom, u);
        }
        for(auto &vtid : u.neighbours) {
            Edge v = readEdgeFromFile(vtid);
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

    return ans;
}


// std::list<DNode*> genGraph(DNode *st) {
//     int ct = 10000;
//     std::list<DNode*> nodes;
//     nodes.push_back(st);
//     for(int i=1; i<ct; ++i) {
//         DNode* u = new DNode;
//         char n = 'a' + i;
//         u->name = std::string(1, n);
//         nodes.push_back(u);
//     }

//     int edct = 20000;
//     std::random_device dev;
//     std::mt19937 rng(dev());
//     std::uniform_int_distribution<std::mt19937::result_type> dist6(-100, 100);

//     std::list<DNode*>::iterator it;
//     for(int i=0; i<edct; ++i) {
//         it = nodes.begin();
//         std::advance(it, dist6(rng));
//         DNode *v1 = *it;

//         std::advance(it, dist6(rng));
//         DNode *v2 = *it;
//         int dist = dist6(rng);

//         v1->neighs[v2] = dist;
//         v2->neighs[v1] = dist;
//     }
//     return nodes;
// }
int main() {

    Edge e = readEdgeFromFile(17);

    std::cout<<e.length<<std::endl;

    std::vector<Edge> sn = dijs(1, 328);

    for(auto &e : sn) {
        std::cout<<e.tid<<std::endl;
    }
    // DNode *s = new DNode();
    // s->name = "a";
    // std::list<DNode*> nodes = genGraph(s);

    // // for(auto &v : nodes) {
    // //     std::cout<<v->name<<"->";
    // //     for(auto &u : v->neighs) {
    // //         std::cout<<u.first->name<<","<<u.second<<"; ";
    // //     }
    // //     std::cout<<std::endl;
    // // }
    // std::cout<<"Graph generated"<<std::endl;
    // std::unordered_map<DNode*, double> dist = A_star(s, nodes.front());

    // // for(auto &p : dist) {
    // //     std::cout<<p.first->name<<","<<p.second<<std::endl;
    // // }

    // for(auto &v : nodes) {
    //     delete v;
    // }
    // return 0;

}