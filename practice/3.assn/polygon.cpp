#include <cstdint>
#include <vector>
#include <iostream>
using namespace std;

uint64_t area(vector<pair<int, int>> &points) {
  // This code has signed overflows. :)
  // Please fix this so it correctly evaluates area..!
  uint64_t total = 0;
  uint64_t tdiv = 0;
  bool odd = 0;
  size_t n = points.size();

  for (unsigned i = 0; i < n; i++) {
    unsigned j = (i + 1) % n;
    int64_t x_i = points[i].first;
    int64_t y_i = points[i].second;
    int64_t x_j = points[j].first;
    int64_t y_j = points[j].second;
    tdiv = x_i * (y_j - y_i) - y_i * (x_j - x_i);
    if (tdiv%2 == 0)  total += tdiv/2;
    else{
      if (odd){
        total += (tdiv+1)/2;
        odd = false;
      }  
      else{
        total += (tdiv-1)/2;
        odd = true;
      }
    }
  }

  return total;
}