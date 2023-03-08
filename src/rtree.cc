#include <array>
#include <vector>

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
  // invoke choose_leaf and add to leaf
  Node &chosen_leaf = choose_leaf(root_, e);
  // TODO confirm here that a copy of the `Rectangle` is made and the pointer is copied
  chosen_leaf.children_.emplace_back(e);
  if(chosen_leaf.children_.size() > R_RECORDS_MAX){
    linear_split(chosen_leaf);
  }
  adjust_tree(chosen_leaf); 
}

Node& Rtree::choose_leaf(Node &n, const Node::IdxEntry &e)
{
  if(n.is_leaf_) return n;

  // compute least growth 
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

// given a node with R_RECORDS_MAX + 1 entries, splits it into two node
void Rtree::adjust_tree(Node& n)
{
  
}

// takes a node n of size of R_RECORDS_MAX + 1 and sets the last entry in children_
// to correspond to the child that needs to be adjusted. Should only be called if the 
// size of the children_ vector > R_RECORDS_MAX
Node& Rtree::linear_split(Node &n)
{
  auto nn = n.children_.end()-1;
  // linear_pick_seeds: for each dimension - 
  //  - find the lowest low, the highest high separation
  //  - find the lowest high and the highest low and the corresponding rectangles
  //  - normalise and store them
  // for the max normalised separation, select the two rectangles.
  std::array<std::vector<Node::IdxEntry>::iterator, R_DIM> ll, hl, lh, hh;
  std::fill(ll.begin(), ll.end(), n.children_.begin() + 1); 
  std::fill(lh.begin(), lh.end(), n.children_.begin() + 1);
  std::fill(hh.begin(), hh.end(), n.children_.begin() + 1);
  std::fill(hl.begin(), hl.end(), n.children_.begin() + 1);
  
  for(auto x=n.children_.begin(); x!=n.children_.end(); x++){
    for(int i=0; i<R_DIM; ++i){
      // check for the lowest low in the rectangles
      if(x->first[i].first < ll[i]->first[i].first) ll[i] = x; 
      // check for the lowest high in the rectangles
      if(x->first[i].second < lh[i]->first[i].second) lh[i] = x; 
      // check for the highest low in the rectangles
      if(x->first[i].first > hl[i]->first[i].first) hl[i] = x; 
      // check for the highest high in the rectangles
      if(x->first[i].second > hh[i]->first[i].second) hh[i] = x; 
    }
  }

  int chosen_dim = 0;
  float max_norm_sep = 0.0;
  for(int i=0; i<R_DIM; ++i){
    //calculate separation
    int sep = hl[i]->first[i].first - lh[i]->first[i].second;
    int dim_width = hh[i]->first[i].second  - ll[i]->first[i].first;
    float norm_sep = static_cast<float>(sep)/dim_width;
    if( norm_sep >  max_norm_sep){
      max_norm_sep = norm_sep;
      chosen_dim = i;
    }
  }
  
  // the dimension that has the max normalised separation and the two referenced rectangles
  // are the seeds to the two split nodes 
  


}


