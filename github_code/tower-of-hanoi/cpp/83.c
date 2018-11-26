// https://www.lintcode.com/problem/tower-of-hanoi/description
#include <string>
#include <vector>
using namespace std;

class Solution {
  public:
    /**
     * @param n: the number of disks
     * @return: the order of moves
     */
    vector<string> s;
    vector<string> towerOfHanoi(int n) {
        // write your code here
        move(n, "A", "B", "C");
        return s;
    }

    void move(int n, string source, string buffer, string destination) {
        if (n <= 0)
            return;
        move(n - 1, source, destination, buffer);
        s.push_back("from " + source + " to " + destination);
        move(n - 1, buffer, source, destination);
    }
};