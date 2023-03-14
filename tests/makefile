debug:
	g++  -DR_RECORDS_MAX=40 -pg -O3 -std=c++14 -DDEBUG -g -Wall -o test_rtree_float test_rtree_float.cc ../src/rtree.cc -I../
	g++  -DR_RECORDS_MAX=40 -pg -O3 -std=c++14 -DDEBUG -g -Wall -o test_rtree_int test_rtree_int.cc ../src/rtree.cc -I../

all:
	g++  -DR_RECORDS_MAX=40 -pg -O3 -std=c++14 -g  -Wall -o test_rtree_float test_rtree_float.cc ../src/rtree.cc -I../
	g++  -DR_RECORDS_MAX=40 -pg -O3 -std=c++14 -g  -Wall -o test_rtree_int test_rtree_int.cc ../src/rtree.cc -I../