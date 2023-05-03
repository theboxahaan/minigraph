#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstring>
#include <set>
#include <cstdio>
// #include "rapidxml-1.13/rapidxml.hpp"
void printRestOfFile(const char* filename, long offset) {
    FILE* file = fopen(filename, "r");
    if (file == nullptr) {
        return;
    }
    fseek(file, offset, SEEK_SET);
    int c;
    while ((c = fgetc(file)) != EOF) {
        putchar(c);
    }
    fclose(file);
}

int main(void)
{
	
	printRestOfFile("edge.txt", 27212);
    return 0;
}