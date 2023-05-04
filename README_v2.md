There are two sets of tasks that this library handles. One is setting up the database itself and the other to query the database.

### Setting up the database:

1. <preprocessing stuff goes here>
2. Generate Indices:
    - Hash Index: First set the file locations for the TID file and Indirection File as obtained from the previous step by calling: include/edge.h: void setFileLocs(std::string tidf, std::string off). Then make a call to src/hashIndex: void genIndex() to generate the index files. 
    A test run can be found in tests/test_gen_hash_index.cc (g++ -std=c++14 test_gen_hash_index.cc; ./a.out)



### Quering the database:

There are two APIs, one for named queries and one for coordinate queries. The named query API at api/inter.cc and the coordinate query API is at api/inter_coords.cc. The function names describe the type of query accurately.

1. To test named queries compile and run test_named_query.cc (g++ -std=c++14 test_named_query.cc; ./a.out)
