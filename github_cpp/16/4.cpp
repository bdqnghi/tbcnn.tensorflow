//给一个list的string，顺序是排好了的，让找出每个字母的大小关系, 不是原ascii的顺序。比如：1. ""ky"" 2. ""kt"" 3. ""ktz""
//4. ""kta"" 5. ""kz"" 6. ""ya"". 由1和2可知t>y, 2,3没什么结论，3,4 推出 a>z, 4,5 推出z>t, 5,6 推出y>k.
//    1. 给出关系结果，就是[""t>y"", ""a>z"", ""z>t"", ""y>k""].
//    2. 如何把上面的关系总结成一个关系，就是从["t>y", "a>z", "z>t", "y>k"]总结出a>z>t>y>k

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

//2. input: list of tuples (A, B) , (B, C). A.tall > B.tall, B.tall > C.tall, 然后给 一个新的tuple (X, Y)，找出这两者
//   的身高关系, 输出X比Y高还是矮还是unknown