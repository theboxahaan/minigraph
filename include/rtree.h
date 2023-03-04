#ifndef MINIGRAPH_RTREE_H
#define MINIGRAPH_RTREE_H

#include <vector>
#include <array>
// // the MiniPoint class only contains the coordinates and no properties. Bare minimum
// // class for a point.
// class MiniPoint {
//   private:
//     const float x_;
//     const float y_;
//   
//   public:
//     MiniPoint(float x, float y): x_{x}, y_{y} {}
//     MMiniPoint(MiniPoint &&o): x_{o.x_}, y_{o.y_} {}
// 
// };
// 
// // basic class that contains a vector of unque_ptrs to MiniPoint objects designating 
// // ownership.
// class MiniBox{
//   private:
//     // assuming that points in a MiniBox will need to be accessed frequently. So placing them
//     // contiguously.
//     std::vector<std::unique_ptr<MiniPoint>> children_;
// 
//   public:
//     MiniBox();
// 
// };


//compile time const to allocate space for R_DIM*2 constrains in the Node
static const int R_DIM = 2; 
static const int R_RECORDS_MAX = 9;
class Rectangle{
  private:
    std::array<std::pair<int, int>, R_DIM> vertices_;
    int area_;
  public:
    Rectangle(const std::array<std::pair<int, int>, R_DIM> &vertices) :
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

};


#endif

