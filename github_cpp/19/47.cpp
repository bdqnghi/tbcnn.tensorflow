#include <vector>
#include <iostream>

void prefix_function(const std::string& s, std::vector<int>& p) {
  p.clear();
  p.resize(s.size());
  p[0] = 0;
  for (int i = 1; i < s.size(); ++i) {
    int j = p[i - 1];
    while (j > 0 && s[i] != s[j]) {
      j = p[j - 1];
    }
    if (s[i] == s[j]) {
      ++j;
    }
    p[i] = j;
  }
}

std::vector<int> substring(const std::string& text,  const std::string& s) {
  std::vector<int> pi, ret;
  prefix_function(s + "@@@" + text, pi);
  for (int i = 0; i < pi.size(); ++i) {
    if (pi[i] == s.size()) {
      ret.push_back(i - 2*(int)s.size());
    }
  }
  return ret;
}

std::vector<int> substring_count(const std::string& text) {
  std::vector<int> pi;
  prefix_function(text, pi);
  std::vector<int> ans(pi.size() + 1, 0);
  for (int i = 0; i < pi.size(); ++i) {
    ++ans[pi[i]];
  }
  for (int i = (int)pi.size() - 1; i > 0 ; --i) {
    ans[pi[i-1]] += ans[i];
  }
  return ans;
}

int main() {
  std::string s = "aabaabc";
  std::vector<int> v(s.length());
  prefix_function(s, v);
  for (int i = 0; i < s.length(); ++i) {
    std::cout << v[i] << " ";
  }
  std::cout << std::endl << "------------" << std::endl;
  auto res = substring("test string", "str");
  for (int i = 0; i < res.size(); ++i) {
    std::cout << "substring starts: " << res[i] << std::endl;
  }
  std::cout << std::endl << "------------" << std::endl;
  res = substring_count("test string te");
  for (int i = 0; i < res.size(); ++i) {
    std::cout << "substring count: " << res[i] << std::endl;
  }
}