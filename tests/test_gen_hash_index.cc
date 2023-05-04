#include "../src/hashIndex.cc"

#ifndef HEADER_H
#define HEADER_H
#include "../include/edge.h"
#endif

int main() {
    setFileLocs("../preprocessing/final_edges/Berkeley/edge_final_berkeley.txt", "../preprocessing/final_edges/Berkeley/tid_offset_final_berkeley.txt");
    genIndex();
}