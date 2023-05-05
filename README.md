There are two sets of tasks that this library handles. One is setting up the database itself and the other to query the database.

### Setting up the database:

1. Prepocessing:
    - Please refer to the two Jupyter Notebooks (Berkeley.ipynb and WL.ipynb) for detailed step-by-step istructions. The final outputs can be seen at ./prepocessing/final_edges .
2. Generating the R-Tree:
    - After copying an edge_final_{WL/Berkeley}.txt file to ./tests and changing test_datainsert.cpp to reflect which file is in the directory (hardcoded), run  ./build_tests.sh; ./test_datainsert . This builds the R-Tree in base.db.
3. Generate Indices:
    - Hash Index: First set the file locations for the TID file and Indirection File as obtained from the previous step by calling: include/edge.h: void setFileLocs(std::string tidf, std::string off). Then make a call to src/hashIndex: void genIndex() to generate the index files. 
    A test run can be found in tests/test_gen_hash_index.cc (g++ -std=c++14 test_gen_hash_index.cc; ./a.out)



### Querying the database:

There are two APIs, one for named queries and one for coordinate queries. The named query API at api/inter.cc and the coordinate query API is at api/inter_coordinate.cc. The function names describe the type of query accurately. The output of the functions are as follows:

1. SSSP: Returns a vector of Edges. The first Edge is a dummy edge which stores the distance between the soruce and destination as its TID, followed by edges from source to destination.

2. KNN: Returns a K-sized vector of vector of Edges. For each vector, the first Edge is a dummy edge which stores the distance between the soruce and destination as its TID, followed by edges from source to target type.

3. Range: Returns a variable sized vector of vector of Edges. The size depends on the number of hits of the type. For each vector, the first Edge is a dummy edge which stores the distance between the soruce and destination as its TID, followed by edges from source to target type.


To test named queries compile and run test_named_query.cc (g++ -std=c++14 test_named_query.cc; ./a.out).

To test point-to-point queries compile and run test_coords_query.cc (g++ -DDEBUG -std=c++14 test_coords_query.cc ../src/rtree.cc -I ../; ./a.out).

Please note, the points and names are hardcoded.
