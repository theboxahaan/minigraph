#include "include/rtree.h"


// insert a new index entry (E) into the R-tree
// E := std::array<std::pair<int, int>>, R_DIM>, tuple pointer

int Rectangle::enlargement(const Rectangle &arg)
{
  int t_area = 1;
  for( auto r_iter=vertices_.cbegin(), arg_iter = arg.vertices_.cbegin();
      r_iter != vertices_.end() && arg_iter != arg.vertices_.end();
      ++r_iter, ++arg_iter){
    
    auto dim = std::max(r_iter->second, arg_iter->second) - std::min(r_iter->first, arg_iter->first);
    t_area *= dim;
  }
  return t_area - area_;
}

void Rtree::insert(const Rectangle &e)
{
  // invoke choose_leaf
  Node &chosen_leaf = choose_leaf(root_, e);
  if(chosen_leaf.records_size_ < R_RECORDS_MAX){
    chosen_leaf.records_.emplace_back(e);
  } else {
    // call split_node 

  
  }
}

Node& Rtree::choose_leaf(Node &n, const Rectangle &e)
{
  Node &N = n;
  if(N.is_leaf_) return N;

  //compute least enlargement
  int min_inc = INT_MAX;
  auto ret_iter = N.children_.begin(); 
  for(auto node_it=N.children_.begin(); node_it!=N.children_.end(); ++node_it){
    int t_inc = (*node_it)->bbox_.enlargement(e);
    if(t_inc < min_inc){
      min_inc = t_inc;
      ret_iter = node_it;
    } else if(t_inc == min_inc){
        ret_iter = (*node_it)->bbox_.area() > (*ret_iter)->bbox_.area()? node_it:ret_iter;
    }
  }
  return choose_leaf(**ret_iter, e);
}

