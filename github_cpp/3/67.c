
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <chrono>
#include <time.h>

#include "node_b.h"
#include "avltree_b.h"
#include "node_h.h"
#include "avltree_h.h"
#include "node_rb.h"
#include "rbtree.h"

std::vector<int> loadTest(std::string filename);
std::vector<int> createDeleteVector(int n);
void testingAVLB(std::vector<int> testNumbers, std::vector<int> numbersToDelete, int testNum);
void testingAVLH(std::vector<int> testNumbers, std::vector<int> numbersToDelete, int testNum);
void testingRB(std::vector<int> testNumbers, std::vector<int> numbersToDelete, int testNum);
void writeSyntax();

int main(int argc, char* argv[]){
    if(argc < 4)
    {
        std::cout << "Incorrect Argument number" << std::endl;
        writeSyntax();
        return 1;
    }
    bool testAVLH = false;
    bool testAVLB = false;
    bool testRB = false;
    switch(argv[1][0])
    {
        case 'B':
            testAVLB = true;
            break;
        case 'H':
            testAVLH = true;
            break;
        case 'R':
            testRB = true;
            break;
        case 'A':
            testAVLB = true;
            testAVLH = true;
            testRB = true;
            break;
        default:
            std::cout << "Invalid first Argument." << std::endl;
            writeSyntax();
            return 1;
    }
    int testNum = atoi(argv[3]);
    if(testNum <=0)
    {
        std::cout << "Invalid third argument!" << std::endl;
        std::cout << "The third argument should be a positive number." << std::endl;
        return 1;
    }

    std::cout << "Loading test input . . . ";
    std::vector<int> testNumbers = loadTest(argv[2]);
    std::vector<int> numbersToDelete = createDeleteVector(testNumbers.size());
    std::cout << "done!" << std::endl;

    if(testAVLB) 
    {
        testingAVLB(testNumbers,numbersToDelete, testNum);
    }
    if(testAVLH) 
    {
        testingAVLH(testNumbers,numbersToDelete, testNum);
    }
    if(testRB) 
    {
        testingRB(testNumbers,numbersToDelete, testNum);
    }
    return 0;
}



std::vector<int> loadTest(std::string filename)
{
    std::vector<int> ret;

    std::ifstream infile;
    infile.open(filename.c_str());
    if(!infile.is_open())
    {
        std::cout << "Error while opening input file: " << filename << std::endl;
        exit(1);
    }
    int input_tmp;
    while(infile >> input_tmp)
    {
        ret.push_back(input_tmp);
    }
    infile.close();
    return ret;
}

std::vector<int> createDeleteVector(int n)
{
    srand (time(NULL));
    std::vector<int> ret;
    for(int i = 0; i < n/5; ++i)
    {
        ret.push_back(rand() % n);
    }
    return ret;
}


void testingAVLB(std::vector<int> testNumbers, std::vector<int> numbersToDelete, int testNum)
{

    std::cout << "Testing AVL-tree type B . . . ";
    NodeB* root_B = NULL;
    AvlTreeB treeMaker_B;
    double avgInsertTime = 0;
    double avgDeleteTime = 0;
    double avgSearchTime = 0;
    for(int i = 0; i < testNum; ++i)
    {
        
        auto begin = std::chrono::high_resolution_clock::now();
        for(std::vector<int>::iterator it = testNumbers.begin(); it != testNumbers.end(); ++it)
        {
            treeMaker_B.insert(root_B, *it);
        }
        auto end = std::chrono::high_resolution_clock::now();
        avgInsertTime += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        begin = std::chrono::high_resolution_clock::now();
        for(std::vector<int>::iterator it = numbersToDelete.begin(); it != numbersToDelete.end(); ++it)
        {
            treeMaker_B.del(root_B, *it);
        }
        end = std::chrono::high_resolution_clock::now();
        avgDeleteTime += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        begin = std::chrono::high_resolution_clock::now();
        for(std::vector<int>::iterator it = testNumbers.begin(); it != testNumbers.end(); ++it)
        {
            treeMaker_B.getNode(root_B, *it);
        }
        end = std::chrono::high_resolution_clock::now();
        avgSearchTime += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();

        delete root_B;
        root_B = NULL;
    }
    std::cout << "Done!" << std::endl;
    avgInsertTime /= testNum;
    avgDeleteTime /= testNum;
    avgSearchTime /= testNum;
    std::cout << "\tBuild time: " << avgInsertTime / 1000000000.0 << "s" << std::endl;
    std::cout << "\tDelete time: " << avgDeleteTime / 1000000000.0 << "s" << std::endl;
    std::cout << "\tSearch time: " << avgSearchTime / 1000000000.0 << "s" << std::endl;
    delete root_B;
}


void testingAVLH(std::vector<int> testNumbers, std::vector<int> numbersToDelete, int testNum)
{
    std::cout << "Testing AVL-tree type H. . . ";
    NodeH* root_H = NULL;
    AvlTreeH treeMaker_H;
    double avgInsertTime = 0;
    double avgDeleteTime = 0;
    double avgSearchTime = 0;
    for(int i = 0; i < testNum; ++i)
    {
        
        auto begin = std::chrono::high_resolution_clock::now();
        for(std::vector<int>::iterator it = testNumbers.begin(); it != testNumbers.end(); ++it)
        {
            treeMaker_H.insert(root_H, *it);
        }
        auto end = std::chrono::high_resolution_clock::now();
        avgInsertTime += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        begin = std::chrono::high_resolution_clock::now();
        for(std::vector<int>::iterator it = numbersToDelete.begin(); it != numbersToDelete.end(); ++it)
        {
            treeMaker_H.del(root_H, *it);
        }
        end = std::chrono::high_resolution_clock::now();
        avgDeleteTime += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        begin = std::chrono::high_resolution_clock::now();
        for(std::vector<int>::iterator it = testNumbers.begin(); it != testNumbers.end(); ++it)
        {
            treeMaker_H.getNode(root_H, *it);
        }
        end = std::chrono::high_resolution_clock::now();
        avgSearchTime += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();

        delete root_H;
        root_H = NULL;
    }
    std::cout << "Done!" << std::endl;
    avgInsertTime /= testNum;
    avgDeleteTime /= testNum;
    avgSearchTime /= testNum;
    std::cout << "\tBuild time: " << avgInsertTime / 1000000000.0 << "s" << std::endl;
    std::cout << "\tDelete time: " << avgDeleteTime / 1000000000.0 << "s" << std::endl;
    std::cout << "\tSearch time: " << avgSearchTime / 1000000000.0 << "s" << std::endl;
    delete root_H;
}

void testingRB(std::vector<int> testNumbers, std::vector<int> numbersToDelete, int testNum)
{
    std::cout << "Testing Red-Black Tree. . . ";
    RBTree treeMaker_RB;
    
    
    double avgInsertTime = 0;
    double avgDeleteTime = 0;
    double avgSearchTime = 0;
    for(int i = 0; i < testNum; ++i)
    {
        
        auto begin = std::chrono::high_resolution_clock::now();
        for(std::vector<int>::iterator it = testNumbers.begin(); it != testNumbers.end(); ++it)
        {
            treeMaker_RB.insert(*it);
        }
        auto end = std::chrono::high_resolution_clock::now();
        avgInsertTime += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        treeMaker_RB.del(38);
        
        begin = std::chrono::high_resolution_clock::now();
        for(std::vector<int>::iterator it = numbersToDelete.begin(); it != numbersToDelete.end(); ++it)
        {
            treeMaker_RB.del(*it);
        }
        end = std::chrono::high_resolution_clock::now();
        avgDeleteTime += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        
        begin = std::chrono::high_resolution_clock::now();
        for(std::vector<int>::iterator it = testNumbers.begin(); it != testNumbers.end(); ++it)
        {
            treeMaker_RB.getNode(*it);
        }
        end = std::chrono::high_resolution_clock::now();
        avgSearchTime += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();

        treeMaker_RB.reset();
    }
    std::cout << "Done!" << std::endl;
    avgInsertTime /= testNum;
    avgDeleteTime /= testNum;
    avgSearchTime /= testNum;
    std::cout << "\tBuild time: " << avgInsertTime / 1000000000.0 << "s" << std::endl;
    std::cout << "\tDelete time: " << avgDeleteTime / 1000000000.0 << "s" << std::endl;
    std::cout << "\tSearch time: " << avgSearchTime / 1000000000.0 << "s" << std::endl;
        
}

void writeSyntax()
{
    std::cout << "The first argument should be \"B\", \"H\", \"R\" or \"A\" depending on the type of the Tree you want to test" << std::endl;
    std::cout << "\t\"B\"\t-\tAVL-Tree using balance" << std::endl;
    std::cout << "\t\"H\"\t-\tAVL-Tree using heights" << std::endl;
    std::cout << "\t\"R\"\t-\tRed-Black Tree" << std::endl;
    std::cout << "\t\"A\"\t-\tAll the above" << std::endl;
    std::cout << "The second Argument should be the name of the test input file inside of the \"test_inputs\" folder" << std::endl;
    
    std::cout << "The third Argument should be the number of times you want to test with the actual test input" << std::endl;
}