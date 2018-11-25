#ifndef mbl_minimum_spanning_tree_h_
#define mbl_minimum_spanning_tree_h_





#include <vector>
#include <iostream>
#include <utility>
#include <vnl/vnl_matrix.h>
#include <vgl/vgl_point_2d.h>
#include <vgl/vgl_point_3d.h>
#ifdef _MSC_VER
#  include <vcl_msvc_warnings.h>
#endif






void mbl_minimum_spanning_tree(const vnl_matrix<double>& D,
                              std::vector<std::pair<int,int> >& pairs);






void mbl_minimum_spanning_tree(const std::vector<vgl_point_2d<double> >& pts,
                              std::vector<std::pair<int,int> >& pairs);






void mbl_minimum_spanning_tree(const std::vector<vgl_point_3d<double> >& pts,
                              std::vector<std::pair<int,int> >& pairs);

#endif 
