#ifndef MINIGRAPH_RTREE_H
#define MINIGRAPH_RTREE_H

#include <vector>
#include <array>
#include <fstream>
#include <iomanip>

#ifdef DEBUG
#include <iostream>
#endif

typedef float Dim;
typedef float UDim;

static const int R_WIDTH = 16;


#ifndef R_DIM 
static const int R_DIM = 2; 
#endif

#ifndef R_RECORDS_MAX
static const int R_RECORDS_MAX = 12; 
#endif

typedef std::array<std::pair<Dim, Dim>, R_DIM> VertexArray;

class Rectangle{
  private:
    VertexArray vertices_;
    UDim area_;
    
  public:
    Rectangle(const VertexArray &vertices) :
      vertices_{vertices} 
    {
      UDim t_area = 1;
      for(auto &x : vertices) t_area *= (x.second - x.first);
      area_ = t_area;
    }

    std::pair<Dim, Dim>& operator[](size_t index){
      // FIXME PERFCHECK no bounds check here ---
      return vertices_[index];
    }

    UDim growth(const Rectangle &r) const;
    void enlarge(const Rectangle &r);
    inline UDim area() {return area_;}
    void dump_to_stream(std::ofstream &fd) const
    {
      for(auto &x: vertices_){
        fd << x.first << "," << x.second - x.first << ",";
      }
      fd << "\n" ;
    }
};


extern std::ofstream db_out;
extern std::ifstream db_in;

class Node_d {
  private:
    // FIXME leaf nodes have nullptrs 
    size_t tid_=0;
    std::vector<std::pair<Rectangle, size_t>> children_d_;
    bool is_leaf_d_;
    size_t parent_d_=0;
    size_t offset_d_=0;
    friend class Rtree;
    Node_d(size_t parent, bool is_leaf=true);

  public:
    void parse_node(size_t);
    void write_node(bool eph=false);

    void push_back_d(const std::pair<Rectangle, size_t> &e) 
    {
      #ifdef DEBUG
      std::cout << "[child+] " << tid_ << " <-- " << e.second << " @ " << children_d_.size() << std::endl;
      #endif
      // update the reverse pointer from child to the corresponding item of the children_d_ array
      if(e.second){
        // read the child from disk
        auto n = Node_d(0, false);
        n.parse_node(e.second);
        n.offset_d_ = children_d_.size();
        n.write_node(true);
        // exit();
      }

      children_d_.emplace_back(e);
      write_node(true);
    }

    Rectangle compute_bounding_rectangle();
    
    inline size_t size() const { return children_d_.size(); }

    ~Node_d()
    {
      #ifdef DEBUG
      // std::cout << "[dstroy] " << this << std::endl;
      #endif
      // for(auto &x: children_d_)if(x.second)delete x.second;
      // children_d_.clear();
    }
};

class Node {
  private:
    // FIXME leaf nodes have nullptrs 
    size_t tid_;
    size_t num_children_=0;

    std::vector<std::pair<Rectangle, Node*>> children_;
    std::vector<std::pair<Rectangle, size_t>> children_d_;

    bool is_leaf_;
    bool is_leaf_d_;

    Node *parent_ = nullptr;
    size_t parent_d_=0;
    
    size_t offset_;   // reverse ptr to the index in the children_ array
    size_t offset_d_;

    friend class Rtree;
    friend class PageMaker;
    // TODO think of a better solution
    // private constructor for now to prevent init on the stack.
    // nobody should need to initialise a node

    Node(Node* parent, bool is_leaf=true);
    // size_t Node_d(size_t parent_d, bool is_leaf_d=true);

  public:
    void push_back(const std::pair<Rectangle, Node*> &e) 
    {
      #ifdef DEBUG
      std::cout << "[child+] " << this << " <-- " << e.second << " @ " << children_.size() << std::endl;
      #endif
      if(e.second)e.second->offset_ = children_.size();
      children_.emplace_back(e);
      num_children_++;
    }
    Rectangle compute_bounding_rectangle();
    
    inline size_t size() const { return children_.size(); }

  
    ~Node()
    {
      #ifdef DEBUG
      std::cout << "[dstroy] " << this << std::endl;
      #endif
      for(auto &x: children_)if(x.second)delete x.second;
      children_.clear();
    }
};

typedef std::pair<Rectangle, Node*> IdxEntry;
typedef std::pair<Rectangle, size_t> IdxEntryD;

typedef std::vector<IdxEntry> IdxEntryVector;
typedef std::vector<IdxEntryD> IdxEntryVectorD;



// implementing the RTree paper by Guttman A. 
// Ref - http://www-db.deis.unibo.it/courses/SI-LS/papers/Gut84.pdf
// TODO add minimum/maximum dimension checks

class Rtree {
  private:
    IdxEntryVector root_;
    IdxEntryVectorD root_d_;

  public:
    Rtree()
    {
      #ifdef DEBUG
      std::cout << "[rtree] create" << std::endl;
      #endif
      VertexArray tmp;
      std::fill(tmp.begin(), tmp.end(), std::pair<Dim, Dim>{0,0});
      // root_.emplace_back(IdxEntry{Rectangle(tmp), new Node(nullptr)});
      //create root Node_d
      std::ofstream gdb_out("base.db", std::ios_base::trunc);
      // gdb_out << "";
      db_out << "HEADER" << std::endl;
      Node_d r = Node_d(0, true);
      r.write_node();
      root_d_.emplace_back(IdxEntryD{Rectangle(tmp), r.tid_});
      
    }

    Node& search();

    Node& choose_leaf(Node &, const IdxEntry& );
    size_t choose_leaf_d(size_t, const IdxEntryD& );
    
    
    void insert(const IdxEntry& );
    void insert_d(const IdxEntryD& );

    Node* adjust_tree(Node*, Node*);
    size_t adjust_tree_d(size_t, size_t);

    void linear_pick_seeds();
    
    Node* linear_split(Node& );
    size_t linear_split_d(size_t );

    ~Rtree()
    {
      #ifdef DEBUG
      std::cout << "[rtree] destroy" << std::endl;
      #endif
      // for(auto &x: root_) delete x.second;
      // root_.clear();
    }

    void walk() const;
    void walk_d() const;
    Node* read_from_offset(size_t p) const;

};


#endif
