#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <set>
#include "Interfaces04.h"
#include "TestCase.h"
#include "Stopwatch.h"
#include "Grader04.h"
#include <cmath>
#include <fstream>
#include "Commands04.h" 

void Grader04::inorderTraversal(std::set<int>& rb_tree, std::vector<int>& rb_sorted)
{
  std::set<int>::iterator iter = rb_tree.begin();
  while(iter != rb_tree.end()){
    rb_sorted.push_back(*iter);
    ++iter;
  }
}

void Grader04::inorderTraversal(IAVLTreeNode * curr, std::vector<int>& sorted)
{
  if(curr == NULL){
    return;
  }
  inorderTraversal(curr->getLeft(), sorted);
  sorted.push_back(curr->getKey());
  inorderTraversal(curr->getRight(), sorted);
}
  
int Grader04::calcHeight(IAVLTreeNode * curr)
{
  if(curr == NULL){
    return 0;
  }
  int left_height = calcHeight(curr->getLeft());
  int right_height = calcHeight(curr->getRight());
  if(left_height > right_height){
    return left_height + 1;
  } else {
    return right_height + 1;
  }
}

void printVector(std::vector<int>& vec){
  std::cout << "vec: " << std::endl;
  for(size_t i = 0; i < vec.size(); ++i){
    std::cout << "  " << vec[i] << std::endl;
  }
}

TestCase * Grader04::testAVLTree(std::string cmds_filename)
{
  std::vector<AVLTreeCmd> commands;
  Commands04 cmds04;
  cmds04.loadAVLTreeCommands(cmds_filename, commands);

  if(commands.size() == 0){
    return failed("cannot load input file");
  }

  std::set<int> rb_tree;

  Stopwatch watch;
  watch.start();
  IAVLTree * avl_tree = (IAVLTree *) createObject("IAVLTree");
  if(avl_tree == NULL){
    return nullObject("IAVLTree");
  }
  
  for(size_t i = 0; i < commands.size(); ++i){
    AVLTreeCmd cmd = commands[i];
    if(cmd.action == AVL_CMD_INSERT){
      //std::cout << "insert: " << cmd.input << std::endl;
      avl_tree->insert(cmd.input);
      rb_tree.insert(cmd.input);
    } else if(cmd.action == AVL_CMD_REMOVE){
      //std::cout << "remove: " << cmd.input << std::endl;
      avl_tree->remove(cmd.input);
      rb_tree.erase(cmd.input);
    } else if(cmd.action == AVL_CMD_CHECK_SORT){
      //std::cout << "check_sort: " << std::endl;
      std::vector<int> rb_sorted;
      inorderTraversal(rb_tree, rb_sorted);

      IAVLTreeNode * root = avl_tree->getRoot();
      if(root == NULL){
        if(rb_sorted.size() == 0){
          continue;
        } else {
          return failed("null root returned from getRoot");
        }
      }
      std::vector<int> avl_sorted;
      inorderTraversal(root, avl_sorted);
      int left_height = calcHeight(root->getLeft());
      int right_height = calcHeight(root->getRight());
      int diff = right_height - left_height;
      if(diff >= 2 || diff <= -2){
        return failed(std::string("error in avl height. cmd_index: ")+toString(i)+std::string(". max_diff: ")+toString(diff));
      }
      if(vectorEqual(rb_sorted, avl_sorted) == false){
        return failed(std::string("error in inorder traversal. cmd_index: ")+toString(i));
      }
    } else if(cmd.action == AVL_CMD_KTH){
      //std::cout << "kth" << std::endl;      
      int kth = avl_tree->kthMin(cmd.input);
      if(kth != cmd.output){
        return failed(std::string("error in kth min. cmd_index: ")+toString(i)+std::string(". k: ")+toString(cmd.input)+std::string(". expected: ")+toString(cmd.output)+std::string(". given: ")+toString(kth));
      }
    } else {
      return failed("internal error in test case");
    }
  }

  watch.stop();

  return passed(watch.getTime());
}

TestCase * Grader04::checkSort(std::vector<RTreePoint>& harness_sorted,
  std::vector<RTreePoint>& gold_sorted){
  
  if(gold_sorted.size() != harness_sorted.size()){
    return failed("hilbert sorted size incorrect");
  }
  
  for(size_t i = 0; i < gold_sorted.size(); ++i){
    RTreePoint gold_point = gold_sorted[i];
    RTreePoint measured_point = harness_sorted[i];

    if(gold_point.x != measured_point.x){
      return failed(std::string("x coord mismatch at index ")+toString(i));
    }
    if(gold_point.y != measured_point.y){
      return failed(std::string("y coord mismatch at index ")+toString(i));
    }
  }
  return passed(0);
}
TestCase * Grader04::testRTreeHilbert(std::string points_filename, 
  std::string sorted_filename, std::string sorted_filename2)
{
  std::vector<RTreePoint> points;
  std::vector<RTreePoint> gold_sorted;
  std::vector<RTreePoint> gold_sorted2;

  Commands04 cmds04;
  cmds04.loadRTreePoints(points_filename, points);
  cmds04.loadRTreePoints(sorted_filename, gold_sorted);
  cmds04.loadRTreePoints(sorted_filename2, gold_sorted2);

  if(points.size() == 0 || gold_sorted.size() == 0 || gold_sorted2.size() == 0){
    return failed("cannot load input file");
  }

  Stopwatch watch;
  watch.start();
  IRTree * rtree = (IRTree *) createObject("IRTree");
  if(rtree == NULL){
    return nullObject("IRTree");
  }

  std::vector<IPoint *> product_points;
  for(size_t i = 0; i < points.size(); ++i){
    RTreePoint curr = points[i];
    IPoint * new_point = (IPoint *) createObject("IPoint");
    if(new_point == NULL){
      return nullObject("IPoint");
    }
    new_point->setX(curr.x);
    new_point->setY(curr.y);
    product_points.push_back(new_point);
  }

  rtree->hilbertSort(product_points);

  std::vector<RTreePoint> harness_sorted;
  for(size_t i = 0; i < product_points.size(); ++i){
    IPoint * product_point = product_points[i];
    RTreePoint harness_point;
    harness_point.x = product_point->getX();
    harness_point.y = product_point->getY();
    harness_sorted.push_back(harness_point);
  }
  watch.stop();
  
  TestCase * ret1 = checkSort(harness_sorted, gold_sorted);
  TestCase * ret2 = checkSort(harness_sorted, gold_sorted2);
  
  if(ret1->passed == true){
    return passed(watch.getTime());
  } else if(ret2->passed == true){
    return passed(watch.getTime());
  } else {
    return ret2;  
  }
}
  
TestCase * Grader04::testRTree(std::string points_filename, std::string cmds_filename)
{  
  std::vector<RTreePoint> points; 
  std::vector<RTreeCmd> cmds;

  Commands04 cmds04;
  cmds04.loadRTreePoints(points_filename, points);
  cmds04.loadRTreeCommands(cmds_filename, cmds);

  if(points.size() == 0 || cmds.size() == 0){
    return failed("cannot load input file");
  }

  Stopwatch watch;
  watch.start();
  IRTree * rtree = (IRTree *) createObject("IRTree");
  if(rtree == NULL){
    return nullObject("IRTree");
  }

  std::vector<IPoint *> product_points;
  for(size_t i = 0; i < points.size(); ++i){
    RTreePoint curr = points[i];
    IPoint * new_point = (IPoint *) createObject("IPoint");
    if(new_point == NULL){
      return nullObject("IPoint");
    }
    new_point->setX(curr.x);
    new_point->setY(curr.y);
    product_points.push_back(new_point);
  }

  rtree->hilbertSort(product_points);
  rtree->bulkInsert(product_points);

  for(size_t i = 0; i < cmds.size(); ++i){
    RTreeCmd cmd = cmds[i];
    IPoint * top_left = (IPoint *) createObject("IPoint");
    if(top_left == NULL){
      return nullObject("IPoint");
    }
    IPoint * bottom_right = (IPoint *) createObject("IPoint");
    if(bottom_right == NULL){
      return nullObject("IPoint");
    }
    top_left->setX(cmd.top_left_x);
    top_left->setY(cmd.top_left_y);
    bottom_right->setX(cmd.bottom_right_x);
    bottom_right->setY(cmd.bottom_right_y);
    std::vector<IPoint *> measured_found = rtree->findWithin(top_left, bottom_right);
    std::set<RTreePoint> gold_found = cmd.found;

    if(gold_found.size() != measured_found.size()){
      return failed(std::string("findWithin returns incorrect number of points. expected: ")+toString(gold_found.size())+std::string(" measured: ")+toString(measured_found.size()));
    }

    for(size_t i = 0; i < measured_found.size(); ++i){
      IPoint * measured_point = measured_found[i];
      int measured_x = measured_point->getX();
      int measured_y = measured_point->getY();

      watch.pause();
      RTreePoint measured_set_point;
      measured_set_point.x = measured_x;
      measured_set_point.y = measured_y;
      if(gold_found.find(measured_set_point) == gold_found.end()){
        return failed("findWithin returns point that cannot be found in gold set");
      }
      watch.unpause();
    }
  }


  watch.stop();
  return passed(watch.getTime());
}

int Grader04::checkBTreeHeight(IBTreeNode * curr)
{
  if(curr == NULL){
    return 0;
  }

  std::vector<IBTreeNode *> stack;
  std::vector<int> dir;
  std::set<IBTreeNode *> visited;

  stack.push_back(curr);
  dir.push_back(0);

  int ret = 0;

  if(curr->isLeaf()){
    return 1;
  }
  
  while(stack.empty() == false){
    int curr_index = dir[dir.size()-1];
    IBTreeNode * node = stack[stack.size()-1];
    if(node == NULL){
      dir.pop_back();
      stack.pop_back();
      continue;
    }

    int height = stack.size();
    if(height > ret){
      ret = height;
    }
    if(curr_index < node->getChildSize()){
      IBTreeNode * child = node->getChild(curr_index);
      if(child->isLeaf()){
        (dir[dir.size()-1])++;
      } else if(visited.find(child) == visited.end()){
        dir.push_back(0);
        stack.push_back(child);
        visited.insert(child);
      } else {
        (dir[dir.size()-1])++;
      }
    } else {
      dir.pop_back();
      stack.pop_back();
    }
  }

  return ret;
}

void Grader04::inorderBTreeTraversal(IBTreeNode * curr, std::vector<int>& visit_order)
{
  if(curr == NULL){
    return;
  }

  std::vector<IBTreeNode *> stack;
  std::vector<int> dir;
  std::set<IBTreeNode *> visited;

  stack.push_back(curr);
  dir.push_back(0);

  if(curr->isLeaf()){
    for(int i = 0; i < curr->getKeySize(); ++i){
      visit_order.push_back(curr->getKey(i));
    }
    return;
  }
  
  while(stack.empty() == false){
    int curr_index = dir[dir.size()-1];
    IBTreeNode * node = stack[stack.size()-1];
    if(node == NULL){
      dir.pop_back();
      stack.pop_back();
      continue;
    }

    if(node->getKeySize() > 5){
      return;
    }

    if(curr_index < node->getChildSize()){
      IBTreeNode * child = node->getChild(curr_index);
      if(child->isLeaf()){
        for(int i = 0; i < child->getKeySize(); ++i){
          visit_order.push_back(child->getKey(i));
        }
        if(curr_index < node->getKeySize()){
          visit_order.push_back(node->getKey(curr_index));
        }
        (dir[dir.size()-1])++;
      } else if(visited.find(child) == visited.end()){
        dir.push_back(0);
        stack.push_back(child);
        visited.insert(child);
      } else {
        if(curr_index < node->getKeySize()){
          visit_order.push_back(node->getKey(curr_index));
        }
        (dir[dir.size()-1])++;
      }
    } else {
      dir.pop_back();
      stack.pop_back();
    }
  }
}

int Grader04::log3(int value){
  int ret = 0;
  while(value > 1){
    ++ret;
    value /= 3;
  }
  return ret;
}

TestCase * Grader04::testBTree(std::string cmds_filename)
{
  std::vector<BTreeCmd> commands;

  Commands04 cmds04;
  cmds04.loadBTreeCommands(cmds_filename, commands);

  if(commands.size() == 0){
    return failed("cannot load input file");
  }

  std::set<int> rb_tree;
  Stopwatch watch;
  watch.start();
  IBTree * b_tree = (IBTree *) createObject("IBTree");
  if(b_tree == NULL){
    return nullObject("IBTree");
  }

  for(size_t i = 0; i < commands.size(); ++i){
    BTreeCmd cmd = commands[i];
    if(cmd.action == BTREE_CMD_INSERT){
      //std::cout << "insert: " << cmd.input << std::endl;
      b_tree->insert(cmd.input, 5);
      rb_tree.insert(cmd.input);
    } else if(cmd.action == BTREE_CMD_REMOVE){
      //std::cout << "remove: " << cmd.input << std::endl;
      b_tree->remove(cmd.input, 5);
      rb_tree.erase(cmd.input);
    } else if(cmd.action == BTREE_CMD_CHECK_SORT){
      //std::cout << "check sort" << std::endl;

      std::vector<int> rb_sorted;
      inorderTraversal(rb_tree, rb_sorted);

      IBTreeNode * root = b_tree->getRoot();
      if(root == NULL){
        if(rb_sorted.size() == 0){
          continue;
        } else {
          return failed("null root returned from getRoot");
        }
      }

      std::vector<int> btree_sorted;
      inorderBTreeTraversal(root, btree_sorted);

      if(rb_sorted.size() != btree_sorted.size()){
        return failed(std::string("error in btree size. cmd_index: ")+toString(i)+std::string(". expected: ")+toString(rb_sorted.size())+std::string(". given: ")+toString(btree_sorted.size()));
      }

      if(vectorEqual(rb_sorted, btree_sorted) == false){
        return failed(std::string("error in inorder traversal. cmd_index: ")+toString(i));
      }

      int height_check = checkBTreeHeight(root);
      int accepted_height = log3((rb_sorted.size() + 1) / 2) + 1;
      if(height_check > accepted_height){
        return failed(std::string("your height is too large. accepted: ")+toString(accepted_height)+std::string(" yours: ")+toString(height_check));
      }

    } else if(cmd.action == BTREE_CMD_KTH){
      //std::cout << "kth: " << cmd.input << std::endl;
      int kth = b_tree->kthMin(cmd.input);
      if(kth != cmd.output){
        return failed(std::string("error in kth min. cmd_index: ")+toString(i)+std::string(". k: ")+toString(cmd.input)+std::string(". expected: ")+toString(cmd.output)+std::string(". given: ")+toString(kth));
      }
    } else {
      return failed("internal error in test case");
    }
  }

  watch.stop();
  return passed(watch.getTime());
}

int Grader04::size(){
  return 24;
}

std::string Grader04::getDescription(int test_case)
{
  switch(test_case){
  case 0: return "AVL-Tree Small Insert Ascending";
  case 1: return "AVL-Tree Small Insert Descending";
  case 2: return "AVL-Tree Small Insert Random";
  case 3: return "AVL-Tree Large Insert Ascending";
  case 4: return "AVL-Tree Large Insert Descending";
  case 5: return "AVL-Tree Large Insert Random";
  case 6: return "AVL-Tree Small Insert/Delete Random";
  case 7: return "AVL-Tree Large Insert/Delete Random";
  case 8: return "AVL-Tree Small Insert/Kth Random";
  case 9: return "AVL-Tree Large Insert/Kth Random";
  case 10: return "Hilbert Sort Small";
  case 11: return "Hilbert Sort Large";
  case 12: return "Hilbert R-Tree Small";
  case 13: return "Hilbert R-Tree Large";
  case 14: return "B-Tree Small Insert Ascending";
  case 15: return "B-Tree Small Insert Descending";
  case 16: return "B-Tree Small Insert Random";
  case 17: return "B-Tree Large Insert Ascending";
  case 18: return "B-Tree Large Insert Descending";
  case 19: return "B-Tree Large Insert Random";
  case 20: return "B-Tree Small Insert/Delete Random";
  case 21: return "B-Tree Large Insert/Delete Random";
  case 22: return "B-Tree Small Insert/Kth Random";
  case 23: return "B-Tree Large Insert/Kth Random";
  }
  return "";
}

int Grader04::getPoints(int test_case)
{
  switch(test_case){
  case 0: return 4;
  case 1: return 4;
  case 2: return 4;
  case 3: return 4;
  case 4: return 4;
  case 5: return 4;
  case 6: return 4;
  case 7: return 4;
  case 8: return 4;
  case 9: return 4;
  case 10: return 5;
  case 11: return 5;
  case 12: return 5;
  case 13: return 5;
  case 14: return 4;
  case 15: return 4;
  case 16: return 4;
  case 17: return 4;
  case 18: return 4;
  case 19: return 4;
  case 20: return 4;
  case 21: return 4;
  case 22: return 4;
  case 23: return 4;
  }
  return 0;
}

Date Grader04::getDueDate()
{
  return Date(10, 31, 2013);
}
  
TestCase * Grader04::grade(int index){
  switch(index){
  case 0:
    return testAVLTree("avl_cmds_1.bin");
  case 1:
    return testAVLTree("avl_cmds_2.bin");
  case 2:  
    return testAVLTree("avl_cmds_3.bin");
  case 3:
    return testAVLTree("avl_cmds_4.bin");
  case 4:
    return testAVLTree("avl_cmds_5.bin");
  case 5:
    return testAVLTree("avl_cmds_6.bin");
  case 6:
    return testAVLTree("avl_cmds_7.bin");
  case 7:
    return testAVLTree("avl_cmds_8.bin");
  case 8:
    return testAVLTree("avl_cmds_9.bin");
  case 9:
    return testAVLTree("avl_cmds_10.bin");
  case 10:
    return testRTreeHilbert("rtree_points_1.bin", "rtree_sorted_points_1.bin",
      "rtree_sorted_points_1.bin");
  case 11:
    return testRTreeHilbert("rtree_points_2.bin", "rtree_sorted_points_2.bin",
      "rtree_sorted_points_2a.bin");
  case 12:
    return testRTree("rtree_points_3.bin", "rtree_cmds_3.bin");
  case 13:
    return testRTree("rtree_points_4.bin", "rtree_cmds_4.bin");
  case 14:
    return testBTree("btree_cmds_1.bin");
  case 15:
    return testBTree("btree_cmds_2.bin");
  case 16:
    return testBTree("btree_cmds_3.bin");
  case 17:  
    return testBTree("btree_cmds_4.bin");
  case 18:
    return testBTree("btree_cmds_5.bin");
  case 19:
    return testBTree("btree_cmds_6.bin");
  case 20:
    return testBTree("btree_cmds_7.bin");
  case 21:
    return testBTree("btree_cmds_8.bin");
  case 22:
    return testBTree("btree_cmds_9.bin");
  case 23:
    return testBTree("btree_cmds_10.bin");
  default:
    return NULL;
  }
}
