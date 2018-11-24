/********************************************************************
**                Image Component Library (ICL)                    **
**                                                                 **
** Copyright (C) 2006-2013 CITEC, University of Bielefeld          **
**                         Neuroinformatics Group                  **
** Website: www.iclcv.org and                                      **
**          http://opensource.cit-ec.de/projects/icl               **
**                                                                 **
** File   : ICLMath/demos/quad-tree/quad-tree.cpp                  **
** Module : ICLMath                                                **
** Authors: Christof Elbrechter                                    **
**                                                                 **
**                                                                 **
** GNU LESSER GENERAL PUBLIC LICENSE                               **
** This file may be used under the terms of the GNU Lesser General **
** Public License version 3.0 as published by the                  **
**                                                                 **
** Free Software Foundation and appearing in the file LICENSE.LGPL **
** included in the packaging of this file.  Please review the      **
** following information to ensure the license requirements will   **
** be met: http://www.gnu.org/licenses/lgpl-3.0.txt                **
**                                                                 **
** The development of this software was supported by the           **
** Excellence Cluster EXC 277 Cognitive Interaction Technology.    **
** The Excellence Cluster EXC 277 is a grant of the Deutsche       **
** Forschungsgemeinschaft (DFG) in the context of the German       **
** Excellence Initiative.                                          **
**                                                                 **
********************************************************************/


#include <ICLQt/Common.h>
#include <ICLUtils/Random.h>
#include <ICLMath/QuadTree.h>

#if 0
template<int N>
int p2() { return 2*p2<N-1>(); }
template<> int p2<1>(){ return 2; }
template<> int p2<0>(){ return 1; }

/// Always uses 2^32 resolution
template<int TREE_LEVELS=6,int LEAVE_LEVELS=4>
struct QuadTree2{
  typedef FixedColVector<int,2> Pt;
  struct Node{
    Node():children(0),on(0){}
    Node *children;
    bool *on;
  };

  Node *root;

  QuadTree2() {
    root = new Node;
  }

  void insert(const Pt &p){
    insert(p[0],p[1]);
  }

  void insert(int x, int y){
    Node *n = root;
    for(int i=0;i<TREE_LEVELS;++i){
      if(!n->children) n->children = new Node[4];
      n = n->children + (x&1 + 2 * y&1);
      x >>= 1;
      y >>= 1;
    }
    static const int X = p2<LEAVE_LEVELS>();

    if(!n->on){
      n->on = new bool[X*X];
      memset(n->on,0,X*X);
    }
    n->on[x + X * y] = true;
  }

  int nn(int x, int y){
    // dunno!
  }
};
#endif

Time t;
std::string what;
inline void tic(const std::string &what){
  ::what = what;
  t = Time::now();
}

inline void toc(){
  std::cout << "Time for " << what << ": " << t.age().toMilliSecondsDouble() << "ms" << std::endl;
}

void init(){
  HBox gui;

  gui << Plot().handle("plot").minSize(64*0.7,48*0.7) << Show();

  PlotHandle plot = gui["plot"];

  //GRandClip rx(320,3*32, Range64f(0,640));
  //GRandClip ry(240,3*24, Range64f(0,480));
  URand rx(0,639), ry(0,479);

  typedef QuadTree<icl32s,32,1,1024> QT;
  typedef QT::Pt Pt;
  QT t(Size::VGA);
  //  QuadTree2<> t2;

  // create data
  std::vector<Pt> ps(100*1000);
  for(size_t i=0;i<ps.size();++i){
    ps[i] = Pt(rx,ry);
  }

  // insert data into the QuadTree
  ::tic("insertion");
  for(size_t i=0;i<ps.size();++i){
    t.insert(ps[i]);
  }
  ::toc();

#if 0
  ::tic("insertion t2");
  for(size_t i=0;i<ps.size();++i){
    t2.insert(ps[i]);
  }
  ::toc();
#endif

  //  t.printStructure();

  plot->sym('x');
  plot->scatter(ps.data(),ps.size());


  /// Query a huge rectangular region with 57% coverage
  Rect r(100,100,500,350);
  ::tic("query");
  for(int i=0;i<100;++i){
    ps = t.query(r);
  }
  ::toc();


  // visualize
  plot->color(0,255,0);
  plot->rect(r);
  plot->scatter(ps.data(),ps.size());
  plot->setDataViewPort(Rect32f(0,0,640,480));
  plot->setPropertyValue("tics.x-distance",50);
  plot->setPropertyValue("tics.y-distance",50);

  plot->nofill();
  plot->color(0,100,255);
  VisualizationDescription d = t.vis();
  plot->draw(d);
  plot->color(255,100,0);


  // create seed points for nn-search
  ps.resize(1000);
  for(size_t i=0;i<ps.size();++i){
    ps[i] = Pt(rx,ry);
  }
  std::vector<Pt> nn(ps.size());

  // precaching ...
  for(size_t i=0;i<ps.size();++i){
    nn[i] = t.nn(ps[i]);
  }

 /// for each seed point: find nn
  ::tic("approx nearest neighbor search");
  for(size_t i=0;i<ps.size();++i){
    nn[i] = t.nn_approx(ps[i]);
  }
  ::toc();

#if 1
  /// for each seed point: find nn
  ::tic("nearest neighbor search");
  for(size_t i=0;i<ps.size();++i){
    nn[i] = t.nn(ps[i]);
  }
  ::toc();
#endif



  // visualize nn-search results
  plot->sym('o');
  plot->linewidth(2);
  plot->scatter(ps.data(),ps.size());
  for(size_t i=0;i<ps.size();++i){
    Pt p = ps[i], n = nn[i];
    plot->line(p[0],p[1],n[0],n[1]);
  }
}


int main(int n, char **ppc){
  return ICLApp(n,ppc,"",init).exec();
}
