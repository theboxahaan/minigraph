#ifndef MINIGRAPH_RTREE_H
#define MINIGRAPH_RTREE_H

#include <vector>
#include <array>
#include <iostream>

//compile time const to allocate space for R_DIM*2 constraints in the Node
static const int R_DIM = 2; 
static const int R_RECORDS_MAX = 4; 

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
    // FIXME leaf nodes have nullptrs 
    std::vector<std::pair<Rectangle, Node*>> children_;
    bool is_leaf_;
    Node *parent_ = nullptr;
    friend class Rtree;
  public:
    Node(bool is_leaf=true, Node* parent=nullptr):is_leaf_{is_leaf}, parent_{parent}
    {
      #ifdef DEBUG
        std::cout << "[create] " << this << "(leaf=" << is_leaf_ << ", parent=" << parent_ <<")" <<  std::endl;
      #endif
    }
    void push_back(const std::pair<Rectangle, Node*> &e) 
    {
      #ifdef DEBUG
       std::cout << "[child+] " << this << " <-- " << e.second << std::endl;
      #endif
      children_.emplace_back(e);
    }
    Rectangle compute_bounding_rectangle();
};

typedef std::pair<Rectangle, Node*> IdxEntry;
typedef std::vector<IdxEntry> IdxEntryVector;

// implementing the RTree paper by Guttman A. 
// Ref - http://www-db.deis.unibo.it/courses/SI-LS/papers/Gut84.pdf
// TODO add minimum/maximum dimension checks

class Rtree {
  private:
    IdxEntryVector root_;

  public:
    Rtree()
    {
      VertexArray tmp;
      std::fill(tmp.begin(), tmp.end(), std::pair<int, int>{0,0});
      root_.emplace_back(IdxEntry{Rectangle(tmp), new Node()});
    }

    Node& search();
    IdxEntryVector::iterator choose_leaf(IdxEntryVector::iterator, const IdxEntry& );
    void insert(const IdxEntry& );
    Node* adjust_tree(Node*, Node*);
    void linear_pick_seeds();
    Node* linear_split(Node& );
    // ~Rtree();
};


#endif

