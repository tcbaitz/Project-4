// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// Test program for checking syntax of a hash table-based dictionary

#include "book.hpp"

#include "hashdict.hpp"

int main(int argc, char** argv) {
  unsigned int inc = 10000;
  hashdict<unsigned int, unsigned int> dict(inc, -1);
  int val;

  dict.insert(10, 10);
  if ((val = dict.find(10)) != -1)
    cout << "Found value " << val << " to match key value 10\n";
  else
    cout << "Nothing found to match key value 10\n";


}
