#include<string>
#include<iostream>

#include "../api/inter.cc"

int main() {
    std::string source = "Dwight Way ";
    std::string dest = "Arden Road ";

    // std::string source = "North Martin Jischke Drive ";
    // std::string dest = "Lawson Hall (LWSN) ";

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<Edge> sn = name_sssp(source, dest);
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout<<"Dijsktra: "<<duration.count()<<std::endl;



    for(auto &e : sn) {
        std::cout<<e.tid<<" ";
    }
    std::cout<<std::endl;


    start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<Edge>> eds = name_KNN(source, "school", 10);
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

    eds = name_range(source, "school", 10000);

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