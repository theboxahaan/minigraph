#include <array>
#include <vector>
#include <climits>
#include <fstream>
#include <stack>
#include <unordered_set>

#ifdef DEBUG
  #include <iostream>
#endif

#include "include/rtree.h"

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

void Rtree::insert(const IdxEntry &e)
{
  auto chosen_leaf_iter = choose_leaf(root_.begin(), e);
  #ifdef DEBUG
    std::cout << "[insert] in leaf(size): " << chosen_leaf_iter->second 
    << "(" << chosen_leaf_iter->second->size() << ")" << std::endl;
  #endif
  Node &chosen_leaf = *chosen_leaf_iter->second;
  chosen_leaf.push_back(e);
  Node *new_node = nullptr;
  if(chosen_leaf.size() > R_RECORDS_MAX){
    std::cout << "gonna split" << std::endl;
    new_node = linear_split(chosen_leaf);
  }
  // FIXME 
  // chosen_leaf_iter->first = chosen_leaf.compute_bounding_rectangle();
  // new_node = adjust_tree(chosen_leaf.parent_, new_node);
  new_node = adjust_tree(&chosen_leaf, new_node);

  if(new_node){
    // root was split so create a new node and add it as the parent of the child nodes
    std::cout << "new root now" << std::endl;
    auto new_root = new Node(false, nullptr);
    new_root->push_back(IdxEntry(new_node->compute_bounding_rectangle(), new_node));
    new_root->push_back(IdxEntry(*root_.begin()));
    root_.begin()->second->parent_ = new_root;
    new_node->parent_ = new_root;
    root_.begin()->second = new_root;
    root_.begin()->first = new_root->compute_bounding_rectangle();
    #ifdef DEBUG
      std::cout << "[nwroot] " << new_root << std::endl;
      for(auto &x: new_root->children_){
        std::cout << "\t[child_] " << x.second << std::endl;
      }
    #endif
  }
}

IdxEntryVector::iterator Rtree::choose_leaf(IdxEntryVector::iterator n, const IdxEntry &e)
{
  Node &cur_node = *n->second;
  if(cur_node.is_leaf_) return n;
  auto next_idx = cur_node.children_.begin();
  int min_inc =  INT_MAX;
  for(auto it=cur_node.children_.begin(); it!=cur_node.children_.end(); ++it){
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

// add nn to n and then propagate split as required
Node* Rtree::adjust_tree(Node *n, Node *nn)
{
  // if(n == nullptr) return nn;
  if(n->parent_ == nullptr) return nn;
  #ifdef DEBUG
    std::cout << "[adjust] " << n << std::endl; 
  #endif
  n->parent_->children_[n->offset_].first = n->compute_bounding_rectangle();
  if(nn){
    n->parent_->push_back(IdxEntry(nn->compute_bounding_rectangle(), nn));
    nn = nullptr;
    if(n->parent_->size() > R_RECORDS_MAX) {
      nn = linear_split(*n->parent_);
    }
  }
  return adjust_tree(n->parent_, nn);
}

Node* Rtree::linear_split(Node &n)
{
  // linear_pick_seeds: for each dimension - 
  //  - find the lowest low, the highest high separation
  //  - find the lowest high and the highest low and the corresponding rectangles
  //  - normalise and store them
  // for the max normalised separation, select the two rectangles.
    std::array<IdxEntryVector::iterator, R_DIM> ll, hl, lh, hh;
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
  
  // FIXME offsets_ need to change for both node children
  Node *nn = new Node(true, n.parent_); 
  //remove this IdxEntry from the children_ table of arg node.
  nn->push_back(*hl[chosen_dim]);
  n.children_.erase(hl[chosen_dim]);
  //apart from lh[i] remove M/2 elements from n.children_ ~ linear next
  for(auto it=n.children_.begin(); n.size() > R_RECORDS_MAX/2 && it!=n.children_.end();){
    if(it != lh[chosen_dim]){
      nn->push_back(*it);
      it = n.children_.erase(it);
    } else {
      ++it;
    }
  }
  for(size_t i=0; i<n.children_.size(); ++i){
    if(!n.is_leaf_) n.children_[i].second->offset_ = i;
  } 
  #ifdef DEBUG
    std::cout << "[split_] " << &n << "(" << n.size()
    << ")" << " --> "<< nn << "(" << nn->size()<<")" << std::endl;  
  #endif
  
  return nn;
}

void Rtree::walk() const
{
  // do a dfs
  std::ofstream file;
  std::cout << "[opning] rec.log" << std::endl;
  file.open("rec.log", std::ios::out | std::ios::app);
  
  std::unordered_set<Node *> visited;
  std::stack<Node *> s;
  s.push(root_.begin()->second);
  
  while(!s.empty()){
    Node *cur = s.top();
    s.pop();
    if(visited.find(cur) == visited.end()){
      for(auto &child: cur->children_){
        child.first.dump_to_stream(file);
        if(child.second)s.push(child.second);
      }
      visited.insert(cur);
    }

  }
  file.close();
}
