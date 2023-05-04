#include "../include/edge.h"
#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<iomanip> 

#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

#include<iostream>

const long long hwidth = 10;
const long long tidwidth = 10;
const long long buckets = 100;
const std::string hfilenamepref = "./hashIdx/hfile_";



long long hashFunc(std::string &key) {
    std::vector<long long> power = {1, 31,961,29791,923521,28629151,887503681,512613922,891031477,621975598,281243405,718545499,274910315,522219709,188810867,853136842,447241920,864499429,799482117,783945459};
    long long sum = 0;
    long long mod = 1000000007;
    for (int i = 0; i < key.length() && i < 20; i++) {
            sum += (key[i] * power[i]) % mod;
    }
    return (sum % mod) % buckets;
}



void genIndex() {
    const std::string filename = "../preprocessing/edge_final.txt";
    std::map<long long, int> edges;

    std::ifstream file(filename);
    
    if (file.is_open()) {
        Edge edge(0, 0.0f, "", "");
        std::string line;
        while (std::getline(file, line)) {
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
                } else if (key == "name:") {
					iss >> edge.name;

                    std::string temp_name;
                    while(iss >> temp_name){
                        edge.name.append(" ");
                        edge.name.append(temp_name);
                    }
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
                    std::string hfn = hfilenamepref + std::to_string(hashFunc(edge.name));
                    std::ofstream hf(hfn, std::ios_base::app);
                    if(hf.is_open()) {
                        std::cout << edge.name << "\n";

                        hf << edge.name << ";"<< edge.tid << "\n";
                        hf.close();
                    }
                    edge = Edge(0, 0.0f, "", "");
                }
            }
        }
        file.close();
    }
    
}

int search(std::string name) {
    long long getH = hashFunc(name);
    std::string fname = hfilenamepref + std::to_string(getH);
    std::cout<<" file name"<<" "<<fname<<"\n";

    std::ifstream ifile(fname);
    std::string line;

    std::string delimiter = ";";

    if(ifile.is_open()) {
        std::cout<<"found file"<<" "<<getH<<"\n";
        while (std::getline(ifile, line)) {
            std::string token = line.substr(0, line.find(delimiter));
            std::cout<<token<<" "<<line.substr(line.find(delimiter)+1)<<"\n";
            int tid = stoi(line.substr(line.find(delimiter)+1));
            if(token == name) return tid;
        }
        ifile.close();

    }
    
    return -1;
}

int main(){
    // genIndex();
    std::cout<<search("StewartCenter")<<"\n";
    return 0;
}