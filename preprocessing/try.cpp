#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstring>
#include <set>
#include "rapidxml-1.13/rapidxml.hpp"
#include "../include/edge.h"
void writeEdgeToFile(Edge edge, const std::string& filename, const std::string& filename_offset) {
    std::ofstream file(filename, std::ios_base::app); //
    std::ofstream tid_to_offset(filename_offset, std::ios_base::app);
	
    if (file.is_open() && tid_to_offset.is_open()) {
        tid_to_offset << edge.tid <<" "<< (long) file.tellp()<< "\n";
		file << "tid: " << edge.tid << "\n";
        file << "length: " << edge.length << "\n";
        file << "source: " << edge.source << "\n";
        file << "target: " << edge.target << "\n";
        file << "source_coords: " << edge.source_coords << "\n";
        file << "target_coords: " << edge.target_coords << "\n";
        file << "name: " << edge.name << "\n";
        file << "type: " << edge.type << "\n";
        file << "neighbours: ";
        for (unsigned int neighbour : edge.neighbours) {
            file << neighbour << " ";
        }
        file << "\n---next---\n";
        file.close();
		tid_to_offset.close();
    }
}

std::vector<Edge> readEdgesFromFile(const std::string& filename) {
    std::vector<Edge> edges;
    std::ifstream file(filename);
    
    if (file.is_open()) {
		std::cout<<"here"<<std::flush;
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
                    edges.push_back(edge);
                    edge = Edge(0, 0.0f, "", "");
                }
            }
        }
        if (!edge.source.empty()) {
            edges.push_back(edge);
        }
        file.close();
    }
    
    return edges;
}

using namespace rapidxml;
xml_document<> doc;
xml_node<> * graphml_node = NULL;
   
int main(){
	std::vector<Edge> edges = readEdgesFromFile("edge.txt");
    std::cout<<edges[0].name<<std::endl;
	for(auto &x : edges){
		if(x.type != "road"){
			edges[x.neighbours[0]].neighbours.push_back(x.tid);
            x.length = 0;
			x.source = edges[x.neighbours[0]].source;
			x.target = edges[x.neighbours[0]].target;
			// std::cout<<x.tid<<std::endl<<std::flush;
			x.neighbours.pop_back();
		}
	}
	std::remove("edge_final.txt");
	std::remove("tid_offset_final.txt");
	std::cout<<"DONE"<<std::flush;
	for(auto edge: edges){
		writeEdgeToFile(edge, "edge_final.txt", "tid_offset_final.txt");
	}

	return 0;
}