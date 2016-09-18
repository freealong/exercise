#include <iostream>
#include <vector>

#include "Vector.hpp"
#include "List.hpp"

using namespace std;

int main(int argc, char* argv[]) {
  Vector<int> v;
  v.push_back(1);
  v.push_back(2);
  Vector<int> v2;
  v2 = v;
  cout << v[0] << " " << v[1] << endl;
  cout << v2[0] << " " << v2[1] << endl;
  List<int> L;
  return 0;
}
