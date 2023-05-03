
#g++ DEBUG -std=c++14 -g -Wall -o test test_property_container.cc ../src/property_*.cc -I../
g++  -DR_RECORDS_MAX=4  -O3 -std=c++14 -g -pg -Wall -o test_rtree_float test_rtree_float.cc ../src/rtree.cc -I../
g++  -DR_RECORDS_MAX=4  -O3 -std=c++14 -g -pg -Wall -o test_rtree_int test_rtree_int.cc ../src/rtree.cc -I../
#g++ -c -std=c++14 -g -Wall -o test_nodes.o ../src/rtree.cc -I../
