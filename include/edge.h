#include <string>
#include <sstream>
#include <unordered_map>

std::string tidFile = "../preprocessing/final_edges/Berkeley/edge_final_berkeley.txt";
std::string offFile = "../preprocessing/final_edges/Berkeley/tid_offset_final_berkeley.txt";


// const std::string tidFile = "../preprocessing/final_edges/WL/edge_final_wl.txt";
// const std::string offFile = "../preprocessing/final_edges/WL/tid_offset_final_wl.txt";

void setFileLocs(std::string tidf, std::string off) {
    tidFile = tidf;
    offFile = off;
}

class Edge
{
public:
    unsigned int tid;
    float length;
    std::string source;
    std::string target;
    std::string source_coords; 
    std::string target_coords; 
    std::string name;
    std::string type;
    std::vector<unsigned int> neighbours;
    Edge(unsigned int tid_, float l, std::string s, std::string t) : tid{tid_}, length{l}, source{s}, target{t} {}
    Edge() : tid{0}, length{0}, source{""}, target{""} {}
    


    bool operator==(const Edge &other) const {
    return tid == other.tid;
  }
    bool operator<(const Edge &other) const {
        return tid < other.tid;
    }
};

class EdgeHash
{
    public:
    size_t operator() (const Edge &e) const {
        return e.tid;
    }
};

#include <fstream>
#include <vector>

std::unordered_map<int, int> prepOffset() {
    std::unordered_map<int, int> offs;
    std::ifstream file(offFile);
    unsigned int itid, off;
    if (file.is_open())
    {
        while (file >> itid >> off)
        {
            offs[itid] = off;
        }
        file.close();
    }
    return offs;
}

Edge getEdge(std::unordered_map<int, int> &offs, std::ifstream &file, int tid) {
    file.seekg(offs[tid]);

    Edge edge(0, 0.0f, "", "");

    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line)) 
        {
            std::istringstream iss(line);
            std::string key;

           if (iss >> key) {
                if (key == "tid:") {
                    // std::cout << edge.tid <<std::flush;
					iss >> edge.tid;
                } else if (key == "length:") {
                    // std::cout << edge.length <<std::flush;
					iss >> edge.length;
                } else if (key == "source:") {
                    // std::cout << edge.source <<std::flush;
					iss >> edge.source;
                } else if (key == "target:") {
                    // std::cout << edge.target;
					iss >> edge.target;
                } else if (key == "source_coords:") {
                    // std::cout << edge.source_coords;
                    std::string temp_coord;
                    while(iss >> temp_coord){
                        edge.source_coords.append(temp_coord);
                        edge.source_coords.append(" ");
                    }
					
                } else if (key == "target_coords:") {
                    // std::cout << edge.target_coords;
					std::string temp_coord;
                    while(iss >> temp_coord){
                        edge.target_coords.append(temp_coord);
                        edge.target_coords.append(" ");
                    }
                }   else if (key == "name:") {
                    std::string temp_name;
                    while(iss >> temp_name){
                        edge.name.append(temp_name);
                        edge.name.append(" ");
                    }
                    // std::cout << edge.name;
                } else if (key == "type:") {
                    // std::cout << edge.type;
					iss >> edge.type;
                } else if (key == "neighbours:") {
                    edge.neighbours.clear();
                    unsigned int neighbour;
                    while (iss >> neighbour) {
                        edge.neighbours.push_back(neighbour);
                    }
                } else if (key == "---next---") {
                    return edge;
                }
            }
        }
    }
    return edge;
}


// unsigned int getOffset(unsigned int tid)
// {
//     const std::string offFile = "../preprocessing/tid_offset_final.txt";
//     std::ifstream file(offFile);
//     unsigned int itid, off;
//     if (file.is_open())
//     {
//         while (file >> itid >> off)
//         {
//             if (itid == tid)
//                 return off;
//         }
//         file.close();
//     }
//     return 0;
// }

// Edge readEdgeFromFile(unsigned int tid)
// {
//     const std::string tidFile = "../preprocessing/edge_final.txt";

//     std::ifstream file(tidFile);
//     unsigned int offset = getOffset(tid);
//     file.seekg(offset);

//     Edge edge(0, 0.0f, "", "");

//     if (file.is_open())
//     {
//         std::string line;
//         while (std::getline(file, line)) 
//         {
//             std::istringstream iss(line);
//             std::string key;

//            if (iss >> key) {
//                 if (key == "tid:") {
//                     // std::cout << edge.tid <<std::flush;
// 					iss >> edge.tid;
//                 } else if (key == "length:") {
//                     // std::cout << edge.length <<std::flush;
// 					iss >> edge.length;
//                 } else if (key == "source:") {
//                     // std::cout << edge.source <<std::flush;
// 					iss >> edge.source;
//                 } else if (key == "target:") {
//                     // std::cout << edge.target;
// 					iss >> edge.target;
//                 } else if (key == "source_coords:") {
//                     // std::cout << edge.source_coords;
//                     std::string temp_coord;
//                     while(iss >> temp_coord){
//                         edge.source_coords.append(temp_coord);
//                         edge.source_coords.append(" ");
//                     }
					
//                 } else if (key == "target_coords:") {
//                     // std::cout << edge.target_coords;
// 					std::string temp_coord;
//                     while(iss >> temp_coord){
//                         edge.target_coords.append(temp_coord);
//                         edge.target_coords.append(" ");
//                     }
//                 } else if (key == "name:") {
// 					iss >> edge.name;
//                     std::string temp_name;
//                     while(iss >> temp_name){
//                         edge.name.append(temp_name);
//                         edge.name.append(" ");
//                     }
//                     // std::cout << edge.name;
//                 } else if (key == "type:") {
//                     // std::cout << edge.type;
// 					iss >> edge.type;
//                 } else if (key == "neighbours:") {
//                     edge.neighbours.clear();
//                     unsigned int neighbour;
//                     while (iss >> neighbour) {
//                         edge.neighbours.push_back(neighbour);
//                     }
//                 } else if (key == "---next---") {
//                     return edge;
//                 }
//             }
//         }
//         file.close();
//     }

//     return edge;
// }