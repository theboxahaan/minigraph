#include "include/rtree.h"

// insert a new index entry (E) into the R-tree
// E := std::array<std::pair<int, int>>, R_DIM>, tuple pointer

int Rectangle::growth(const Rectangle &arg) const
{
  int t_area = 1;
  for( auto r_iter=vertices_.cbegin(), arg_iter = arg.vertices_.cbegin();
      r_iter != vertices_.end() && arg_iter != arg.vertices_.end();
      ++r_iter, ++arg_iter){
    
    int dim = std::max(r_iter->second, arg_iter->second) - std::min(r_iter->first, arg_iter->first);
    t_area *= dim;
  }
  return t_area - area_;
}

void Rtree::insert(const Node::IdxEntry &e)
{
  // invoke choose_leaf
  Node &chosen_leaf = choose_leaf(root_, e);
  adjust_tree();
}

Node& Rtree::choose_leaf(Node &n, const Node::IdxEntry &e)
{
  if(n.is_leaf_) return n;

  //compute least growth 
  auto next_idx = n.children_.begin();
  int min_inc =  INT_MAX;
  for(auto it=n.children_.begin(); it!=n.children_.end(); ++it){
    int t_inc = it->first.growth(e.first);
    if(t_inc < min_inc){
      min_inc = t_inc;
      next_idx = it;
    } else if(t_inc == min_inc){
        next_idx = next_idx->first.area() < it->first.area() ? next_idx:it;
    }
  }
  return choose_leaf(*(next_idx->second), e);
}

void Rtree::adjust_tree()
{

}

// performs a split linearly on node &n and returns a reference to the split Node
// TODO using `new` now but need to fix it using std::unique_ptr's
Node& Rtree::linear_split(Node &n)
{
  // linear_pick_seeds
  VertexArray arr;  
  auto iter = n.children_.begin();
  for(; iter!= n.children_.end(); ++iter){
    
  }
  
}

void Rtree::linear_pick_seeds()
{

}
