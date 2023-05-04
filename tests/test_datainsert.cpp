#include<vector>
#include<array>
#include<iostream>
#include <unordered_map>

#include "include/edge.h"
#include "include/rtree.h"

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
					iss >> edge.name;
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


int main()
{
  std::cout << "R_DIM: " << R_DIM << ", R_RECORDS_MAX: " << R_RECORDS_MAX << std::endl;


  std::vector<Edge> edges = readEdgesFromFile("edge_final.txt");


    auto rt = Rtree();
    int dddd = 0;
    // std::cout<< "rtree built" << std::endl;
    for(auto edge: edges){
      if(dddd > 10000)
        break;
      dddd++;
      // rt.insert(IdxEntry(Rectangle(x), nullptr));
      std::array<std::pair<Dim, Dim>, 2> mbr;
      
      std::stringstream ss_source(edge.source_coords);
			std::string coord_str_source;
			getline(ss_source, coord_str_source, ',');

      std::stringstream ss_target(edge.target_coords);
			std::string coord_str_target;
			getline(ss_target, coord_str_target, ',');
      mbr[0] = std::pair<Dim, Dim> ({std::stod(coord_str_source), std::stod(coord_str_target)});
      getline(ss_source, coord_str_source, ',');
      getline(ss_target, coord_str_target, ',');
      mbr[1] = std::pair<Dim, Dim> ({std::stod(coord_str_source), std::stod(coord_str_target)});
      if(mbr[0].first - mbr[0].second < 1e-4 || mbr[1].first - mbr[1].second < 1e-4){  
        mbr[0].second += 1e-3;
        mbr[1].second += 1e-3;
      }
      if(mbr[0].first > mbr[0].second)std::swap(mbr[0].first, mbr[0].second);
      if(mbr[1].first > mbr[1].second)std::swap(mbr[1].first, mbr[1].second);
      std::cout<<mbr[0].first<<" "<<mbr[0].second<<" "<<mbr[1].first<<" "<<mbr[1].second<<std::endl;
      rt.insert_d(IdxEntryD(Rectangle(mbr), 0)); 
      // std::cout << "insert" << std::endl; 
    }
    
    //rand_mod = rand_mod * 2;
    //numPoints = numPoints * 2;
    rt.walk_d();

    std::vector<std::array<std::pair<Dim ,Dim>, 2>> input = {
    {{{-86.9138,86.9128},{40.4224,40.4241}}},
  };

    IdxEntryVectorD v;
    rt.search_d(rt.root_d_[0].second, v, Rectangle(input[0]));
    std::cout << "size of results " << v.size() << std::endl;

    for(auto x: v){
        std::cout << "-> " << x.first[0].first << " " << x.first[0].second << " " << x.first[1].first << " " << x.first[1].second << std::endl;
    }

    db_out.close();
    db_in.close();

  return 0;

}
