#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <math.h>
#include "huffman-coding.hpp"

using namespace std;

void read_stdin(string &in) {
  string line;
  while (getline(cin, line)) {
    in += line;
  }
}

struct GreaterWeight {
  bool operator()(const Node* lhs, const Node* rhs) {
    return lhs->weight > rhs->weight;
  }
};

void create_table(const string &input, map<unsigned char, string> &table) {
  map<unsigned char, int> symbols;

  //for (const unsigned char &c : input) {
  for (const auto &c : input) {
    if (symbols.count(c)) {
      symbols[c]++;
    } else {
      symbols[c] = 0;
    }
  }

  priority_queue<Node*, vector<Node*>, GreaterWeight> nodes;

  for (const auto &p : symbols) {
    nodes.push(new LeafNode(p.second, p.first));
  }

  while (nodes.size() > 1) {
    Node* a = nodes.top();
    nodes.pop();
    Node* b = nodes.top();
    nodes.pop();

    Node* node = new InternalNode(a, b);
    nodes.push(node);
  }

  Node* root = nodes.top();
  root->generate_codes(table);
  delete root;
}

void LeafNode::generate_codes(map<unsigned char, string> &table, string prefix) {
  table[this->symbol] = prefix;
}

void InternalNode::generate_codes(map<unsigned char, string> &table, string prefix) {
  this->left->generate_codes(table, prefix + '0');
  this->right->generate_codes(table, prefix + '1');
}

void encode(string &data, map<unsigned char, string> &table, vector<unsigned char> &encoded) {
  string code = "";
  for (const auto &c : data) {
    code += table[c];
  }

  rpad(code, ceil(code.length() / 8.0) * 8);

  for (int i = 0; i < code.length(); i += 8) {
    unsigned char byte = stoi(code.substr(i, 8), NULL, 2);
    encoded.push_back(byte);
  }
}

void decode(vector<unsigned char> &data, map<unsigned char, string> &table, string &decoded) {
  map<string, unsigned char> invertedTable;
  for (const auto &p : table) {
    invertedTable[p.second] = p.first;
  }

  string code = "";
  for (const auto byte : data) {
    string c = itos(byte, 2);
    lpad(c, 8);
    code += c;
  }

  string bits = "";
  for (const auto &c : code) {
    bits += c;
    if (!invertedTable.count(bits)) continue;

    unsigned char symbol = invertedTable[bits];
    if (symbol == eof) break;

    decoded += symbol;
    bits = "";
  }
}

void rpad(string &s, int width) {
  for (int i = 0, len = width - s.length(); i < len; i++) {
    s += '0';
  }
}

void lpad(string &s, int width) {
  for (int i = 0, len = width - s.length(); i < len; i++) {
    s = '0' + s;
  }
}

// http://www.jb.man.ac.uk/~slowe/cpp/itoa.html
string itos(int value, int base) {
  const string digits = "0123456789abcdef";

  int v = value;
  string buf;
  do {
    buf = digits[abs(v % base)] + buf;
    v /= base;
  } while (v);

  if (value < 0) {
    buf = '-' + buf;
  }

  return buf;
}

int main() {
  string input;
  read_stdin(input);
  input += eof;

  map<unsigned char, string> table;
  create_table(input, table);

  vector<unsigned char> encoded;
  encode(input, table, encoded);

  string decoded;
  decode(encoded, table, decoded);

  cout << decoded;
  return 0;
}
