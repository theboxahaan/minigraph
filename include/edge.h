#include <string>
#include <sstream>

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

unsigned int getOffset(unsigned int tid)
{
    const std::string offFile = "../preprocessing/tid_offset.txt";
    std::ifstream file(offFile);
    unsigned int itid, off;
    if (file.is_open())
    {
        while (file >> itid >> off)
        {
            if (itid == tid)
                return off;
        }
        file.close();
    }
    return 0;
}

Edge readEdgeFromFile(unsigned int tid)
{
    const std::string tidFile = "../preprocessing/edge.txt";

    std::vector<Edge> edges;
    std::ifstream file(tidFile);
    unsigned int offset = getOffset(tid);
    file.seekg(offset);

    Edge edge(0, 0.0f, "", "");

    if (file.is_open())
    {
        std::string line;
        int i=0;
        while (std::getline(file, line) && i++ < 6) 
        {
            std::istringstream iss(line);
            std::string key;

            if (iss >> key)
            {
                if (key == "tid:")
                {
                    iss >> edge.tid;
                    // std::cout<<edge.tid<<std::endl;
                }
                else if (key == "length:")
                {
                    iss >> edge.length;
                }
                else if (key == "source:")
                {
                    iss >> edge.source;
                }
                else if (key == "target:")
                {
                    iss >> edge.target;
                }
                else if (key == "neighbours:")
                {
                    edge.neighbours.clear();
                    unsigned int neighbour;
                    while (iss >> neighbour)
                    {
                        edge.neighbours.push_back(neighbour);
                    }
                }
                else if (key == "---next---")
                {
                    return edge;
                }
            }
        }
        file.close();
    }

    return edge;
}