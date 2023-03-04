#ifndef MINIGRAPH_RTREE_H
#define MINIGRAPH_RTREE_H

#include <vector>
#include <array>

//compile time const to allocate space for R_DIM*2 constrains in the Node
static const int R_DIM = 2; 
static const int R_RECORDS_MAX = 9;
typedef std::array<std::pair<int, int>, R_DIM> VertexArray;

class Rectangle{
  private:
    VertexArray vertices_;
    int area_;
  public:
    Rectangle(const VertexArray &vertices) :
      vertices_{vertices} 
    {
      int t_area = 1;
      for(auto &x : vertices){
        t_area *= (x.second - x.first);
      }
      area_ = t_area;
    }
    int enlargement(const Rectangle &r);
    int area() { return area_;}

};
// the index records of the form
// E := (std::array<std::pair<int, int>>, R_DIM>, tuple pointer)
// that are stored in a Node and form the basis of all lookups 

class Node {
  private:
    Rectangle bbox_; 
    int size_;
    int records_size_;
    // FIXME only present if Node is a leaf node
    // some class `E`
    std::vector<Rectangle> records_;
    // TODO do I use pointer indirection or directly store the Nodes here. Sortof a DFS
    // approach to storage. Depends on how big the tree is.
    // FIXME use std::unique_ptr here instead of raw ptr
    std::vector<Node*> children_;
    Node *parent_ = nullptr;
    bool is_leaf_;
    friend class Rtree;
  public:
    Node(Rectangle &r, bool is_leaf):bbox_{r}, is_leaf_{is_leaf} {}
};


// implementing the RTree paper by Guttman A. 
// Ref - http://www-db.deis.unibo.it/courses/SI-LS/papers/Gut84.pdf
// TODO add a proper citation to the comments.

// TODO add minimum/maximum dimension checks


class Rtree {
  private:
    Node &root_ ;
    Rtree();

  public:
    Rtree build_tree();
    Node& search();
    Node& choose_leaf(Node&, const Rectangle& );
    void insert(const Rectangle& );
    void adjust_tree();
    void linear_pick_seeds();
    Node& linear_split(Node& );

};


#endif

