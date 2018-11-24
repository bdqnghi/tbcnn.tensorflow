// ref: http://www.geeksforgeeks.org/greedy-algorithms-set-3-huffman-coding/
// c++ map: http://mropengate.blogspot.tw/2015/12/cc-map-stl.html
#include <iostream>
#include <map>     // map
#include <queue>   // priority_queue
#include <sstream> // string to int
#include <string>  // string

using namespace std;

std::map<char, int> ans;

// A Huffman tree node
struct MinHeapNode {
  char data;                 // 輸入的字元
  unsigned freq;             // 字元頻率
  MinHeapNode *left, *right; // 左右子樹

  // 建構子
  MinHeapNode(char data, unsigned freq) {
    left = right = NULL;
    this->data = data;
    this->freq = freq;
  }
};

// 給 priority_queue 使用的判斷式 讓他變成min heap, top是最小頻率
struct compare {
  bool operator()(MinHeapNode *l, MinHeapNode *r) {
    return (l->freq > r->freq);
  }
};

// 從 root 開始印 huffman codes
void printCodes(struct MinHeapNode *root, string str) {
  // 終止條件(到底之後再往下走 會是空的)
  if (!root) {
    return;
  }

  // 終止條件
  // 如果不是 internal node 代表到底了 可以印答案了
  if (root->data != '$') {
    // string to int
    // ref:
    // https://dotblogs.com.tw/v6610688/2013/11/08/cplusplus_stringstream_int_and_string_convert_and_clear
    stringstream ss;
    int num;
    ss << str;
    ss >> num;
    ans[root->data] = num;
    // 原本印答案的
    // cout << root->data << ":" << str << "\n";
  }

  // 往左走的時候加0
  printCodes(root->left, str + "0");
  // 往右走的時候加1
  printCodes(root->right, str + "1");
}

// 建構 Huffman Tree
void HuffmanCodes(std::map<char, int> &freq) {
  struct MinHeapNode *left, *right, *top;

  // 建立一個含很多個node的min heap, 每一個node都代表一個樹的樹根
  priority_queue<MinHeapNode *, vector<MinHeapNode *>, compare> minHeap;
  for (std::map<char, int>::iterator it = freq.begin(); it != freq.end();
       ++it) {
    minHeap.push(new MinHeapNode(it->first, it->second));
  }

  // 如果minHeap的size只剩一代表只剩一個internal node, 停止
  while (minHeap.size() != 1) {
    // 從min heap中取得最小頻率的兩個字 並pop掉
    left = minHeap.top();
    minHeap.pop();
    right = minHeap.top();
    minHeap.pop();

    // 製造一個 和是兩個最小node 且分別是左右樹葉 的internal node,
    // 並加入minheap,
    // $是一個字元給internal node使用, 不會用到
    top = new MinHeapNode('$', left->freq + right->freq);
    top->left = left;
    top->right = right;
    minHeap.push(top);
  }

  // 停止後開始印答案
  printCodes(minHeap.top(), "");
}

int main() {

  // 輸入文字
  string input = "mississippis";
  cin >> input;
  std::map<char, int> freq;

  // 字串轉頻率的迴圈
  // ref:
  // http://stackoverflow.com/questions/28383292/calculate-frequency-of-each-letter-in-a-string
  for (int i = 0; i < input.size(); ++i) {
    if (freq.find(input[i]) == freq.end()) {
      freq[input[i]] = 1;
    } else {
      freq[input[i]]++;
    }
  }

  // 主要解題
  HuffmanCodes(freq);

  // 為了排序
  int ans_size = 0;
  int *ans_code = new int[ans_size];
  char *ans_char = new char[ans_size];
  for (std::map<char, int>::iterator it = ans.begin(); it != ans.end(); ++it) {
    ans_size++;
    ans_char[ans_size - 1] = it->first;
    ans_code[ans_size - 1] = it->second;
    // 不然直接照字母印就好了QQ
    // cout << it->first << ":" << it->second << "\n";
  }

  // bubble sort
  for (int i = ans_size - 1; i > 0; i--) {
    for (int j = 0; j < i; j++) {
      if (ans_code[j] > ans_code[j + 1]) {
        swap(ans_char[j], ans_char[j + 1]);
        swap(ans_code[j], ans_code[j + 1]);
      }
    }
  }

  // print ans
  for (int i = 0; i < ans_size; i++) {
    cout << ans_char[i] << ":" << ans_code[i] << endl;
  }

  delete[] ans_code;
  delete[] ans_char;

  // system("pause");
  return 0;
}
