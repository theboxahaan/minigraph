#g++ DEBUG -std=c++14 -g -Wall -o test test_property_container.cc ../src/property_*.cc -I../
g++  -DR_RECORDS_MAX=4   -DDEBUG -std=c++14 -g -Wall -o test_rtree test_rtree.cc ../src/*.cc -I../
#g++ -c -std=c++14 -g -Wall -o test_nodes.o ../src/rtree.cc -I../
