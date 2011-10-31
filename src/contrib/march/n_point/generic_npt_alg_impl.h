/*
 *  generic_npt_alg_impl.h
 *  
 *
 *  Created by William March on 8/25/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


template<class TMatcher>
bool npt::GenericNptAlg<TMatcher>::CanPrune_(NodeTuple& nodes) {
  
  return !(matcher_.TestNodeTuple(nodes));
  
} // CanPrune


template<class TMatcher>
void npt::GenericNptAlg<TMatcher>::BaseCase_(NodeTuple& nodes) {
  
  matcher_.ComputeBaseCase(nodes);
  
} // BaseCase_


template<class TMatcher>
void npt::GenericNptAlg<TMatcher>::DepthFirstRecursion_(NodeTuple& nodes) {
  
  if (nodes.all_leaves()) {
    
    BaseCase_(nodes);
    num_base_cases_++;
    
  } 
  else if (CanPrune_(nodes)) {
    
    num_prunes_++;
    
  }
  else {
    
    // split nodes and call recursion
    
    // TODO: can I infer something about one check from the other?
    
    // left child
    if (nodes.CheckSymmetry(nodes.ind_to_split(), true)) {
      // do left recursion
      
      //mlpack::Log::Info << "recursing\n";
      
      NodeTuple left_child(nodes, true);
      DepthFirstRecursion_(left_child);
      
    }
    // TODO: should I count these
    /*
    else {
      mlpack::Log::Info << "symmetry prune\n";
    }
     */
    // right child
    if (nodes.CheckSymmetry(nodes.ind_to_split(), false)) {
      
      //mlpack::Log::Info << "recursing\n";

      NodeTuple right_child(nodes, false);
      DepthFirstRecursion_(right_child);
      
    }
    /*
    else {
      mlpack::Log::Info << "symmetry prune\n";
    }
     */
  
  } // recurse 
  
} // DepthFirstRecursion_


template<class TMatcher>
void npt::GenericNptAlg<TMatcher>::Compute() {
  
  //std::vector<NptNode*> node_list;
  //int next_same = 0;
  
  /*
  for (unsigned int i = 0; i < multiplicities_.size(); i++) {
  
    for (int j = 0; j < multiplicities_[i]; j++) {
      
      node_list.push_back(trees_[i]);
      
    } // for j
    
    next_same++;
    
  } // for i
*/
  //mlpack::Log::Info << "filled in node_list\n";
  
  /*
  data_tree_root_->Print();
  node_list[0]->Print();
  node_list[0]->left()->Print();
  
   */
  
  // matcher needs to know num_random_ too to store counts correctly
  //NodeTuple nodes(node_list, nodes_same);
  NodeTuple nodes(trees_);
  
  if (do_naive_) {
    BaseCase_(nodes);
  }
  else {
    DepthFirstRecursion_(nodes);
  }
    //mlpack::Log::Info << "generic num_base_cases: " << num_base_cases_ << "\n";
  //mlpack::Log::Info << "generic num_prunes: " << num_prunes_ << "\n";
  
} // Compute
