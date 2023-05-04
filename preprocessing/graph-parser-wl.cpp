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
#include <algorithm>

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

#include <fstream>
#include <vector>

std::vector<Edge> readEdgesFromFile(const std::string& filename) {
    std::vector<Edge> edges;
    std::ifstream file(filename);
    
    if (file.is_open()) {
        Edge edge(0, 0.0f, "", "");
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string key;
            if (iss >> key) {
                if (key == "tid:") {
                    iss >> edge.tid;
					// std::cout<<edge.tid<<std::endl;
                } else if (key == "length:") {
                    iss >> edge.length;
                } else if (key == "source:") {
                    iss >> edge.source;
                } else if (key == "target:") {
                    iss >> edge.target;
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

// using namespace std;
using namespace rapidxml;


xml_document<> doc;
xml_node<> * graphml_node = NULL;
   
int main(void)
{
	unsigned int tid_last = 0;
	std::unordered_map<std::string, std::vector<unsigned int>> target_map;
	std::unordered_map<std::string, std::vector<unsigned int>> source_map;

	std::vector<Edge> edges;
    std::remove("edge.txt");
	std::remove("tid_offset.txt");
    // Read the graphml file CHANGE HERE IF NEED BE
    std::ifstream theFile ("wl.graphml");
    std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
    buffer.push_back('\0');
   
    // Parse the buffer
    doc.parse<0>(&buffer[0]);
   
    // Find out the root node
    graphml_node = doc.first_node("graphml");
	xml_node<> * graph_node = graphml_node->first_node("graph");
    for (xml_node<> * edge_node = graph_node->first_node("edge"); edge_node; edge_node = edge_node->next_sibling())
    {
    

		if(edge_node->first_attribute("source") != 0){
			
			// std::cout << "\n edge source =   "<<edge_node->first_attribute("source")->value();
			// std::cout << "\n edge target =   "<<edge_node->first_attribute("target")->value();
			
            
            xml_node<> * d9_node = edge_node->first_node("data");
            while(strcmp(d9_node->first_attribute("key")->value(), "d9") && d9_node->next_sibling()){
				d9_node = d9_node->next_sibling();
			}
            
            std::string name_d10;
            if(!strcmp(d9_node->first_attribute("key")->value(), "d9"))
			    name_d10 = d9_node->value();
            else
                name_d10 = "";




            xml_node<> * d14_node = edge_node->first_node("data");
            while(strcmp(d14_node->first_attribute("key")->value(), "d14")){
				d14_node = d14_node->next_sibling();
			}
			// std::cout << "\n edge weight =   "<<std::stof(d14_node->value());
			// std::cout << std::endl<<std::flush;
			float l = std::stof(d14_node->value());

            xml_node<> * d15_node = edge_node->first_node("data");
			while(strcmp(d15_node->first_attribute("key")->value(), "d15") && d15_node->next_sibling()){
                // std::cout<<d15_node->first_attribute("key")->value()<<std::endl<<std::flush;
				d15_node = d15_node->next_sibling();
			}
            std::string str;
            if(!strcmp(d15_node->first_attribute("key")->value(), "d15"))
			    str = d15_node->value();
            else
                continue;
			// std::cout<<str<<std::endl;
			size_t start = str.find("(");
    		size_t end = str.find(")");
			std::string coords_str = str.substr(start + 1, end - start - 1);

			// Split the substring into individual coordinate pairs
			std::vector<std::string> coords;
			std::stringstream ss(coords_str);
			std::string coord_str;
			while (getline(ss, coord_str, ',')) {
				coords.push_back(coord_str);
			}

			// Extract the first and last coordinate pairs
            std::replace(coords[0].begin(), coords[0].end(), ' ', ',');
            std::replace(coords[coords.size() - 1].begin() + 1, coords[coords.size() - 1].end(), ' ', ','); //+1 to ignore space in beginning of str
			std::string first_coord_pair_str = coords[0];
			std::string last_coord_pair_str = coords[coords.size() - 1];

			// std::cout << "\tFirst coordinate pair: " << first_coord_pair_str << std::endl;
			// std::cout << "\tLast coordinate pair: " << last_coord_pair_str << std::endl;
			std::string s = edge_node->first_attribute("source")->value();
			std::string t = edge_node->first_attribute("target")->value();
			Edge newest_edge(tid_last,l,s,t);
            newest_edge.source_coords = first_coord_pair_str;
            newest_edge.target_coords = last_coord_pair_str;
            newest_edge.name = name_d10;
            newest_edge.type = "road";
			source_map[s].push_back(tid_last);
			target_map[t].push_back(tid_last);
			
			edges.push_back(newest_edge);
            
			++tid_last;
		}
    }

	for(auto target_pair : target_map){
		for(auto target_tid : target_pair.second){
			for(auto source_tid : source_map[target_pair.first])
			edges[target_tid].neighbours.push_back(source_tid); 
		}
	}

	for(auto edge: edges){
		writeEdgeToFile(edge, "edge.txt", "tid_offset.txt");
	}


	// auto new_edges = readEdgesFromFile("edge.txt");
	// for(auto x : new_edges){
	// 	std::cout<<"x:"<<std::endl;
	// 	std::cout<<"\tsource:"<<x.source<<"\ttarget:"<<x.target<<"\tlen:"<<x.length<<std::endl<<"\t";
	// 	for(auto n : x.neighbours){
	// 		std::cout<<n<<" ";
	// 	}
	// 	std::cout<<std::endl;
	// }
    return 0;
}