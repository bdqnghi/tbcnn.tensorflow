

#include <stdio.h>
#include "../../../headers/algorithms.hpp"

using namespace DataStructures;

namespace Algorithms{
    namespace Sorting{
        template <typename V>
        void HeapSort(Vector<V>& input, Vector<V>& output){
            PriorityQueue<V> queue;
            Vector<V> save = input;
            output.Resize(0);

            for(int i = 0; i < save.Size(); i++){
                queue.Push(save[i]);
            }

            for(int i = 0; i < save.Size(); i++){
                output.Insert(queue.Head());
                queue.Pop();
            }
        }
    }
}

template void Algorithms::Sorting::HeapSort<double>(Vector<double>&,Vector<double>&);
template void Algorithms::Sorting::HeapSort<int>(Vector<int>&,Vector<int>&);
template void Algorithms::Sorting::HeapSort<SGraph::Edge>(Vector<SGraph::Edge>&,Vector<SGraph::Edge>&);

