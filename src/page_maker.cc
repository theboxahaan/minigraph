// #include "include/page_maker.h" 

#include <iostream>
#include <fstream>


#include "include/rtree.h"

#define PAGE_SIZE 16384 

class PageMaker {

  private:
    size_t cur_offset = 0;
    std::fstream db;
  public:
    PageMaker()
    {
      db.open("test.db", std::ios::out|std::ios::in|std::ios::binary);
    }
    size_t write_node(Node &);
    Node* read_node(size_t );
    ~PageMaker()
    {
      close(db);
    }

};

// the tid is an offset of size size_t
struct __attribute__ ((packed)) FileNode (
  std::array<std::pair<VertexArray, size_t>, R_RECORDS_MAX> v_;  
  size_t parent_;
};


// write the node to the db file and return the offset to the beginning of the node
size_t PageMaker::write_node(Node &n)
{
  struct FileNode f;
  int idx = 0;
  // a 0 offset means that the offset is unavailable for the corresponding Node
  for(auto x: n->children_){
    f.v_[idx] = {x.first, 0};
  }
  f.parent_ = 0;
  db.write(f, sizeof(f));
  cur_offset += sizeof(f);
}



int main()
{

  // insert the rtree root.
  auto a = PageMaker();
  

  db.close();
  return 0;

}
