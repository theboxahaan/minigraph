#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstring>
#include <set>
#include "rapidxml-1.13/rapidxml.hpp"

class Edge{
public:
	unsigned int tid;
	float length;
	std::string source;
	std::string target;
	std::vector<unsigned int> neighbours;
	Edge(unsigned int tid_, float l, std::string s, std::string t): tid{tid_},length{l},source{s},target{t} {}
};
void writeEdgeToFile(Edge edge, const std::string& filename, const std::string& filename_offset) {
    std::ofstream file(filename, std::ios_base::app); //
    std::ofstream tid_to_offset(filename_offset, std::ios_base::app);
	
    if (file.is_open() && tid_to_offset.is_open()) {
        tid_to_offset << edge.tid <<" "<< (long) file.tellp()<< "\n";
		file << "tid: " << edge.tid << "\n";
        file << "length: " << edge.length << "\n";
        file << "source: " << edge.source << "\n";
        file << "target: " << edge.target << "\n";
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
    // Read the graphml file
    std::ifstream theFile ("graph.graphml");
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
			xml_node<> * d14_node = edge_node->first_node("data");
			while(strcmp(d14_node->first_attribute("key")->value(), "d14")){
				d14_node = d14_node->next_sibling();
			}
			// std::cout << "\n edge weight =   "<<std::stof(d14_node->value());
			// std::cout << std::endl;
			float l = std::stof(d14_node->value());
			std::string s = edge_node->first_attribute("source")->value();
			std::string t = edge_node->first_attribute("target")->value();
			Edge newest_edge(tid_last,l,s,t);
			source_map[s].push_back(tid_last);
			target_map[t].push_back(tid_last);
			// target_map[t].push_back(tid_last);
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

	// for(int i = 0; i < edges.size(); i++){
	// 	std::cout<<"i:"<<i<<std::endl;
	// 	std::cout<<"\tsource:"<<edges[i].source<<"\ttarget:"<<edges[i].target<<"\tlen:"<<edges[i].length<<std::endl<<"\t";
	// 	for(auto n : edges[i].neighbours){
	// 		std::cout<<n<<" ";
	// 	}
	// 	std::cout<<std::endl;
	// }
	
	for(auto edge: edges){
		writeEdgeToFile(edge, "edge.txt", "tid_offset.txt");
		// std::cout<<"edge written:"<<std::endl;
		// std::cout<<"\tsource:"<<edge.source<<"\ttarget:"<<edge.target<<"\tlen:"<<edge.length<<std::endl<<"\t";
		// for(auto n : edge.neighbours){
		// 	std::cout<<n<<" ";
		// }
		// std::cout<<std::endl;
	}


	auto new_edges = readEdgesFromFile("edge.txt");
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