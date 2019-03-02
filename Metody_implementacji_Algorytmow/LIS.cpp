#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

std::string tab;

void showVec(std::vector<size_t>  & v) {
  for(size_t i=0; i<v.size(); i++)
    std::cout << (char)v[i];
  std::cout << "\n";
}

void insertFirstBigger(std::vector<size_t> & vec, size_t value) {
  for (size_t i=0; i < vec.size(); i++) {
    if(vec[i] >= value) {
      vec[i] = value;
      return;
    }
  }
  vec.push_back(value);
}

size_t lis(std::string & data) {
  std::vector<size_t> vec;
  for(size_t i=0; i< data.size(); i++) {
    insertFirstBigger(vec, data[i]);
    // showVec(vec);
  }
  return vec.size();
}

int main() {
    std::string data;
    std::cin >> data;
    size_t res = lis(data);
    std::cout << 26 - res << "\n";
   return 0;
}
