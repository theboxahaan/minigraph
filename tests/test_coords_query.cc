#include<string>
#include<iostream>


#include "../api/inter_coordinate.cc"

int main() {
    std::string source = "Dwight Way ";
    std::string dest = "Arden Road ";
    std::array<std::pair<Dim, Dim>, 2> mbr_source = {{{-122.2445702, -122.2443826}, {37.8590061 ,37.8598274 }}};
    std::array<std::pair<Dim, Dim>, 2> mbr_dest = {{{-122.2457593,-122.2444017},{37.8607704,37.8608807}}};
    // std::string source = "North Martin Jischke Drive ";
    // std::string dest = "Lawson Hall (LWSN) ";

    auto start = std::chrono::high_resolution_clock::now();
    // std::vector<Edge> sn = name_sssp(source, dest);
    std::vector<Edge> sn = coordinate_sssp(mbr_source, mbr_dest);
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout<<"Dijsktra: "<<duration.count()<<std::endl;



    for(auto &e : sn) {
        std::cout<<e.tid<<" ";
    }
    std::cout<<std::endl;


    start = std::chrono::high_resolution_clock::now();
    // std::vector<std::vector<Edge>> eds = name_KNN(source, "university", 10);
    std::vector<std::vector<Edge>> eds = coordinate_knn(mbr_source, "school", 10);
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

    // eds = name_range(source, "university", 5000);
    eds = coordinate_name_range(mbr_source, "school", 10000);

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