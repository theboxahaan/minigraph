#ifndef MINIGRAPH_RTREE_H
#define MINIGRAPH_RTREE_H

#include <vector>
#include <array>

//compile time const to allocate space for R_DIM*2 constraints in the Node
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
      for(auto &x : vertices) t_area *= (x.second - x.first);
      area_ = t_area;
    }

    std::pair<int ,int>& operator[](int index){
      // FIXME PERFCHECK no bounds check here ---
      return vertices_[index];
    }

    int growth(const Rectangle &r) const;
    void enlarge(const Rectangle &r);
    int area() { return area_;}

};


class Node {
  private:
    //leaf nodes have nullptrs 
    // FIXME use std::uniquq ptrs here later
    typedef std::pair<Rectangle, Node*> IdxEntry;
    std::vector<IdxEntry> children_;
    Node *parent_ = nullptr;
    bool is_leaf_;
    friend class Rtree;
  public:
    Node(bool is_leaf=false):is_leaf_{is_leaf} {}
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
    Node& choose_leaf(Node&, const Node::IdxEntry& );
    void insert(const Node::IdxEntry& );
    void adjust_tree(Node& );
    void linear_pick_seeds();
    Node& linear_split(Node& );

};


#endif

