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
    std::cout<<"Time taken for SSSP (micro s): "<<duration.count()<<std::endl;

    std::cout<<"Distance (m): "<< sn[0].tid<<std::endl;
    std::cout<<"Space separated TIDs from source edge to destination edge"<<"\n";
    for(int j=1; j<sn.size(); ++j) {
        std::cout<<sn[j].tid<<" ";
    }
    std::cout<<std::endl;


    start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<Edge>> eds = name_KNN(source, "school", 10);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout<<"Time taken for KNN (micro s): "<<duration.count()<<std::endl;


    int i=0;
    for(auto &vs : eds) {
        std::cout<<"For Neighbor number: "<<i++<<std::endl;
        std::cout<<"Distance (m): "<< vs[0].tid<<std::endl;
        std::cout<<"Space separated TIDs from source edge to destination edge"<<"\n";
        for(int j=1; j<vs.size(); ++j) {
            std::cout<<vs[j].tid<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;


    start = std::chrono::high_resolution_clock::now();

    eds = name_range(source, "school", 10000);

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout<<"Time taken for range (micro s): "<<duration.count()<<std::endl;


    i=0;
    for(auto &vs : eds) {
        std::cout<<"For Neighbor number: "<<i++<<std::endl;
        std::cout<<"Distance (m): "<< vs[0].tid<<std::endl;
        std::cout<<"Space separated TIDs from source edge to destination edge"<<"\n";
        for(int j=1; j<vs.size(); ++j) {
            std::cout<<vs[j].tid<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

    return 0;
}