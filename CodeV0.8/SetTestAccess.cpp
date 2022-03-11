// get an element randomly from a set
#include <iostream>
#include <set>
#include <algorithm>
#include <ctime>

using namespace std;
 
int main() {
  srand((unsigned int)time(0));
  // generate a set...
  set<int> s;
  for( int i = 0; i != 10; ++i ) s.insert(i);
 
  set<int>::const_iterator it;
  // 'advance' the iterator random times
  advance(it, rand() % s.size());

  cout<<*it<<endl;
  return 0;
}
