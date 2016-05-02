#include <iostream>
#include <cstdlib>
#include <ctime>
#include "hashtable.hpp"

using namespace std;

int main(int argc, char **argv) {
  srand(time(nullptr));
  Hashtable<int> test;
  for (auto i = 0; i < 100; ++i) {
    test.insert(rand());
  }
  std::cout << "Inserted " << test.size() << " unique values." << std::endl;
  cin.ignore();
  return 0;
}
