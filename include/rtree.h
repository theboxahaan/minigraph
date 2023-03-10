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
    // FIXME use std::unique ptrs here later
    typedef std::pair<Rectangle, Node*> IdxEntry;
    typedef std::vector<IdxEntry> IdxEntryVector;
    IdxEntryVector children_;
    Node *parent_ = nullptr;
    bool is_leaf_;
    friend class Rtree;
  public:
    Node(bool is_leaf=true):is_leaf_{is_leaf} {}
    void push_back(IdxEntry &e) 
    {
      children_.emplace_back(e);
    }
    Rectangle compute_bounding_rectangle();
};


// implementing the RTree paper by Guttman A. 
// Ref - http://www-db.deis.unibo.it/courses/SI-LS/papers/Gut84.pdf
// TODO add a proper citation to the comments.

// TODO add minimum/maximum dimension checks


class Rtree {
  private:
    Node::IdxEntryVector root_;

  public:
    Rtree()
    {
      VertexArray tmp;
      std::fill(tmp.begin(), tmp.end(), std::pair<int, int>{0,0});
      root_.emplace_back(Node::IdxEntry{Rectangle(tmp), new Node()});
    }


    Rtree build_tree();
    Node& search();
    Node::IdxEntryVector::iterator choose_leaf(Node::IdxEntryVector::iterator, const Node::IdxEntry& );
    void insert(const Node::IdxEntry& );
    void adjust_tree(Node& );
    void linear_pick_seeds();
    Node* linear_split(Node& );

};


#endif

