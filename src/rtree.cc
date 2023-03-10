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


Rectangle Node::compute_bounding_rectangle()
{
  VertexArray tmp;
  std::array<int, R_DIM> ll, hh;
  std::fill(ll.begin(), ll.end(), INT_MAX); 
  std::fill(hh.begin(), hh.end(), INT_MIN);
  
  for(auto x=children_.begin(); x!=children_.end(); x++){
    for(int i=0; i<R_DIM; ++i){
      // check for the lowest low in the rectangles
      if(x->first[i].first < ll[i]) ll[i] = x->first[i].first; 
      // check for the highest high in the rectangles
      if(x->first[i].second > hh[i]) hh[i] = x->first[i].second; 
    }
  }
  for(int i=0; i<R_DIM; i++) tmp[i] = {ll[i], hh[i]};
  return Rectangle(tmp);
}



void Rtree::insert(const Node::IdxEntry &e)
{
  // invoke choose_leaf and add to leaf
  auto chosen_leaf = choose_leaf(root_.begin(), e);
  // TODO confirm here that a copy of the `Rectangle` is made and the pointer is copied
  chosen_leaf->second->children_.emplace_back(e);
  if(chosen_leaf->second->children_.size() > R_RECORDS_MAX){
    linear_split(*(chosen_leaf->second));
  }
  adjust_tree(*chosen_leaf->second); 
}

std::vector<Node::IdxEntry>::iterator Rtree::choose_leaf(std::vector<Node::IdxEntry>::iterator n, const Node::IdxEntry &e)
{
  if(n->second->is_leaf_) return n;

  auto next_idx = n->second->children_.begin();
  int min_inc =  INT_MAX;
  for(auto it=n->second->children_.begin(); it!=n->second->children_.end(); ++it){
    int t_inc = it->first.growth(e.first);
    if(t_inc < min_inc){
      min_inc = t_inc;
      next_idx = it;
    } else if(t_inc == min_inc){
        next_idx = next_idx->first.area() < it->first.area() ? next_idx:it;
    }
  }
  return choose_leaf(next_idx, e);
}

// given a node with R_RECORDS_MAX + 1 entries, splits it into two node
void Rtree::adjust_tree(Node& n)
{
  
}

Node* Rtree::linear_split(Node &n)
{
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
    int sep = hl[i]->first[i].first - lh[i]->first[i].second;
    int dim_width = hh[i]->first[i].second  - ll[i]->first[i].first;
    float norm_sep = static_cast<float>(sep)/dim_width;
    if( norm_sep >  max_norm_sep){
      max_norm_sep = norm_sep;
      chosen_dim = i;
    }
  }
  
  // FIXME port to std::unique_ptr -- will it introduce overheads? Is the indexing step 
  // performance critical
  Node *nn = new Node(); 
  //remove this IdxEntry from the children_ table of arg node.
  nn->push_back(*hl[chosen_dim]);
  n.children_.erase(hl[chosen_dim]);
  //apart from lh[i] remove M/2 elements from n.children_ ~ linear next
  for(auto it=n.children_.begin(); n.children_.size() > R_DIM/2 && it!=n.children_.end();){
    if(it != lh[chosen_dim]){
      nn->push_back(*it);
      it = n.children_.erase(it);
    } else {
      ++it;
    }
  }
  
  // finally have the split Nodes n and nn
  // add the parent_ reference and return nn so that it can be added to the parent.children_,
  nn->parent_ = n.parent_;
  // compute bounding Rectangle for new node nn and adjust the bounding rectangle for the 
  // old node n
  
  // TODO migrate this call to parent
  // n.parent_->children_.emplace_back({nn->compute_bounding_rectangle(), nn});
  return nn;
}


