//
//  minimum-spanning-tree.cpp
//  graph-repl
//
//  Created by alfons haffmans on 9/18/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "tests.h"


REGISTER_TEST(test_mst_dense_prim);
REGISTER_TEST(test_mst_prim_pfs);
REGISTER_TEST(test_mst_kruskal);
REGISTER_TEST(test_mst_boruvka);

std::pair<int, std::string> test_mst_dense_prim(std::ostream& strm,int argc, const char *argv[])
{
      sparse_graph_t s10(15, graph_type_t::UNDIRECTED);
      
      s10.insert(simple_edge_t(0,1,0.32));//1
      s10.insert(simple_edge_t(0,2,0.29));//2
      s10.insert(simple_edge_t(0,6,0.51));//3
      s10.insert(simple_edge_t(5,3,0.18));//4
      s10.insert(simple_edge_t(7,4,0.46));//5
      s10.insert(simple_edge_t(5,4,0.40));//6
      s10.insert(simple_edge_t(0,5,0.60));//7
      s10.insert(simple_edge_t(6,4,0.51));//8
      s10.insert(simple_edge_t(7,0,0.31));//9
      s10.insert(simple_edge_t(7,6,0.25));//10
      s10.insert(simple_edge_t(7,1,0.21));//11
      s10.insert(simple_edge_t(4,3,0.34));//12
      
      std::string dn = test_path("dense_prim_graph.dot");
      s10.graphviz(dn);
      
      mst<simple_edge_t, mst_prim<simple_edge_t>> P(s10);
      P.pp(strm);
      sparse_graph_t t10(15, graph_type_t::UNDIRECTED);
      P(t10);
      std::string dt = test_path("dense_prim_mst.dot");
      t10.graphviz(dt);
      ASSERT(s10.V() == t10.V());
      ASSERT(s10.E() >= t10.E());
      std::set<simple_edge_t> expected = {simple_edge_t(0,7,0.31),
            simple_edge_t(3,5,0.18),
            simple_edge_t(7,6,0.25),
            simple_edge_t(0,2,0.29),
            simple_edge_t(7,1,0.21),
            simple_edge_t(4,3,0.34),
            simple_edge_t(7,4,0.46)};
      std::vector<simple_edge_t> mst = P();
      ASSERT(expected.size() == mst.size());
      for (auto& ee : expected) {
            strm << ee << " in mst" << std::endl;
            ASSERT(mst.end() != find(mst.begin(), mst.end(), ee));
      }
      strm<< "DONE" <<std::endl;
      return DONE;
}

std::pair<int, std::string> test_mst_prim_pfs(std::ostream& strm,int argc, const char *argv[])
{
      sparse_graph_t s10(15, graph_type_t::UNDIRECTED);
      
      s10.insert(simple_edge_t(0,1,0.32));//1
      s10.insert(simple_edge_t(0,2,0.29));//2
      s10.insert(simple_edge_t(0,6,0.51));//3
      s10.insert(simple_edge_t(5,3,0.18));//4
      s10.insert(simple_edge_t(7,4,0.46));//5
      s10.insert(simple_edge_t(5,4,0.40));//6
      s10.insert(simple_edge_t(0,5,0.60));//7
      s10.insert(simple_edge_t(6,4,0.51));//8
      s10.insert(simple_edge_t(7,0,0.31));//9
      s10.insert(simple_edge_t(7,6,0.25));//10
      s10.insert(simple_edge_t(7,1,0.21));//11
      s10.insert(simple_edge_t(4,3,0.34));//12
      
      std::string dn = test_path("mst_prim_pfs_graph.dot");
      s10.graphviz(dn);
      
      mst<simple_edge_t, mst_prim_pfs<simple_edge_t>> P(s10);
      P.pp(strm);
      sparse_graph_t t10(15, graph_type_t::UNDIRECTED);
      P(t10);
      std::string dt = test_path("mst_prim_pfs.dot");
      t10.graphviz(dt);
      ASSERT(s10.V() == t10.V());
      ASSERT(s10.E() >= t10.E());
      std::set<simple_edge_t> expected = {simple_edge_t(0,7,0.31),
            simple_edge_t(3,5,0.18),
            simple_edge_t(7,6,0.25),
            simple_edge_t(0,2,0.29),
            simple_edge_t(7,1,0.21),
            simple_edge_t(4,3,0.34),
            simple_edge_t(7,4,0.46)};
      std::vector<simple_edge_t> mst = P();
      ASSERT(expected.size() == mst.size());
      for (auto& ee : expected) {
            strm << ee << " in mst" << std::endl;
            ASSERT(mst.end() != find(mst.begin(), mst.end(), ee));
      }
      strm<< "DONE" <<std::endl;
      return DONE;
}

std::pair<int, std::string> test_mst_kruskal(std::ostream& strm,int argc, const char *argv[])
{
      sparse_graph_t s10(15, graph_type_t::UNDIRECTED);
      
      s10.insert(simple_edge_t(0,1,0.32));//1
      s10.insert(simple_edge_t(0,2,0.29));//2
      s10.insert(simple_edge_t(0,6,0.51));//3
      s10.insert(simple_edge_t(5,3,0.18));//4
      s10.insert(simple_edge_t(7,4,0.46));//5
      s10.insert(simple_edge_t(5,4,0.40));//6
      s10.insert(simple_edge_t(0,5,0.60));//7
      s10.insert(simple_edge_t(6,4,0.51));//8
      s10.insert(simple_edge_t(7,0,0.31));//9
      s10.insert(simple_edge_t(7,6,0.25));//10
      s10.insert(simple_edge_t(7,1,0.21));//11
      s10.insert(simple_edge_t(4,3,0.34));//12
      
      std::string dn = test_path("mst_kruskal_graph.dot");
      s10.graphviz(dn);
      
      mst<simple_edge_t, mst_kruskal<simple_edge_t>> P(s10);
      P.pp(strm);
      
      sparse_graph_t t10(15, graph_type_t::UNDIRECTED);
      P(t10);
      std::string dt = test_path("mst_kruskal.dot");
      t10.graphviz(dt);
      ASSERT(s10.V() == t10.V());
      ASSERT(s10.E() >= t10.E());
      std::vector<simple_edge_t> expected = {simple_edge_t(0,7,0.31),
            simple_edge_t(7,0,0.31),
            simple_edge_t(3,5,0.18),
            simple_edge_t(5,3,0.18),
            simple_edge_t(7,6,0.25),
            simple_edge_t(6,7,0.25),
            simple_edge_t(0,2,0.29),
            simple_edge_t(2,0,0.29),
            simple_edge_t(7,1,0.21),
            simple_edge_t(1,7,0.21),
            simple_edge_t(4,3,0.34),
            simple_edge_t(3,4,0.34),
            simple_edge_t(7,4,0.46),
            simple_edge_t(4,7,0.46)};
      std::vector<simple_edge_t> mst = P();
      ASSERT(expected.size() == mst.size()*2);
      for (auto& ee : mst) {
            strm << ee << " in mst" << std::endl;
            ASSERT(expected.end() !=   find(expected.begin(), expected.end(), ee));
      }
      strm<< "DONE" <<std::endl;
      return DONE;
}

std::pair<int, std::string> test_mst_boruvka(std::ostream& strm,int argc, const char *argv[])
{
      sparse_graph_t s10(15, graph_type_t::UNDIRECTED);
      
      s10.insert(simple_edge_t(0,1,0.32));//1
      s10.insert(simple_edge_t(0,2,0.29));//2
      s10.insert(simple_edge_t(0,6,0.51));//3
      s10.insert(simple_edge_t(5,3,0.18));//4
      s10.insert(simple_edge_t(7,4,0.46));//5
      s10.insert(simple_edge_t(5,4,0.40));//6
      s10.insert(simple_edge_t(0,5,0.60));//7
      s10.insert(simple_edge_t(6,4,0.51));//8
      s10.insert(simple_edge_t(7,0,0.31));//9
      s10.insert(simple_edge_t(7,6,0.25));//10
      s10.insert(simple_edge_t(7,1,0.21));//11
      s10.insert(simple_edge_t(4,3,0.34));//12
      
      std::string dn = test_path("mst_boruvka_graph.dot");
      s10.graphviz(dn);
      
      mst<simple_edge_t, mst_boruvka<simple_edge_t>> P(s10);
      P.pp(strm);
      
      sparse_graph_t t10(15, graph_type_t::UNDIRECTED);
      P(t10);
      std::string dt = test_path("mst_boruvka.dot");
      t10.graphviz(dt);
      ASSERT(s10.V() == t10.V());
      ASSERT(s10.E() >= t10.E());
      std::vector<simple_edge_t> expected = {simple_edge_t(0,7,0.31),
            simple_edge_t(7,0,0.31),
            simple_edge_t(3,5,0.18),
            simple_edge_t(5,3,0.18),
            simple_edge_t(7,6,0.25),
            simple_edge_t(6,7,0.25),
            simple_edge_t(0,2,0.29),
            simple_edge_t(2,0,0.29),
            simple_edge_t(7,1,0.21),
            simple_edge_t(1,7,0.21),
            simple_edge_t(4,3,0.34),
            simple_edge_t(3,4,0.34),
            simple_edge_t(7,4,0.46),
            simple_edge_t(4,7,0.46)};
      std::vector<simple_edge_t> mst = P();
      ASSERT(expected.size() == mst.size()*2);
      for (auto& ee : mst) {
            strm << ee << " in mst" << std::endl;
            ASSERT(expected.end() !=   find(expected.begin(), expected.end(), ee));
      }
      strm<< "DONE" <<std::endl;
      return DONE;
}




