// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// Test program for the array-based queue class

//include Emily's implementation of hash
#include "../emHashTable/emHashTable.hpp"

//include separate chaining with linked list
#include "../separateChaining/separateChaining.hpp"

//include linear hashing
#include "../linearHash/LinearHash.cpp"

//include the book's implementation of hash
#include "../bookHash/dictionary.hpp"
#include "../bookHash/hashdict.hpp"
#include "../bookHash/KVpair.hpp"
#include "../bookHash/book.hpp"


#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <limits>
#include <fstream>
#include <iterator>
#include <algorithm>    // std::random_shuffle

#include <map>
#include <unordered_map>

//include time recording files
#include "Complexity_Timer.hpp"
#include "Complexity_Recorder.hpp"

using namespace std;

// timer
timer timer1;

// U can be any type we want to test.
typedef int U;

//total number of algorithims being tested
const int number_of_algorithms = 8;
//the number times the number of elements will be multiplied
const int number_of_trials = 11;

const char* headings[number_of_algorithms] =
{"| Emily's Hash   ",
 "| STL UnOrd Map  ",
 "| S Chain LL Hash",
 "| Book's Dict Has",
 "| Emily's Remove ",
 "| UnOrd Map Remov",
 "| LL Hash Remove ",
 "| Dict Hash Remov"};

int main()
{
    const unsigned int START_SIZE = 32768;
    const unsigned int INCREMENT_FACTOR = 2;
    unsigned int current_size = START_SIZE;
    unsigned int old_size = 0;
//    int max_size = START_SIZE^(INCREMENT_FACTOR*number_of_trials);
// for our outputting of the results
    ofstream ofs("results.txt");

// this is going to hold the measurements
    vector<recorder<timer> > stats(number_of_algorithms);

// The "U" is the type for the queues x and y (poorly named, i know). Using the largest sequence multiplied by factor to allocate memory
    //EMAQueue<U> x(current_size);

    cout << "________";
    for (int i = 0; i < number_of_algorithms; ++i)
      cout << headings[i];
    cout << endl;

    cout << "  Size  ";
    for (int i = 0; i < number_of_algorithms; ++i)
      cout << "|      Time      ";
    cout << endl;

    //initialize vector of ints
    vector<int> testVector;
    //initialize vector of keys
    vector<int> keyVector;
    for (unsigned int i = 0; i < current_size; ++i) {
        testVector.push_back(rand());
        keyVector.push_back(testVector[i]%101);
    }



    for (int count = 0; count < number_of_trials; count ++)
    {
        //displays the number of elements that will be added to the data structures
        cout << setw(8) << current_size << flush;
        ofs << setw(8) << current_size;
        //resets stats
        for (int i = 0; i < number_of_algorithms; ++i)
            stats[i].reset();

        //start of testing
        for (int j = 0; j < number_of_trials; ++j)
        {
            //initialize data structures each trial
            Hashtable<unsigned int> emHash;
            unordered_map<unsigned int, unsigned int> stlMap;
            HashMap sepChain;
            hashdict<unsigned int, unsigned int> bookHash(current_size, -1);
            //does test for each algorithm
            for (int i = 0; i < number_of_algorithms; ++i)
            {
               //resets timer
               timer1.restart();
                //completes the test "current_size" times
            for (unsigned int k = 0; k < current_size; ++k)
            {
                 //data type operations to be tested
                switch (i)
                {
                    //insert values to Emily's Hash
                    case 0: emHash.insert(testVector[k]);
                            //emHash.insert(k);
                        break;
                    case 1: stlMap.insert(make_pair(testVector[k], keyVector[k]));
                            //stlMap.insert(k, k);
                        break;
                    case 2: //sepChain.insert(testVector[k]);
                            //sepChain.insert(k);
                        break;
                    case 3: //bookHash.insert(keyVector[k], testVector[k]);
                            //bookHash.insert(k, k);
                        break;
                    case 4: emHash.remove(testVector[k]);
                            //emHash.remove(k);
                        break;
                    case 5: stlMap.erase(testVector[k]);
                            //stlMap.erase(k);
                        break;
                    case 6: //sepChain.remove(testVector[k]);
                            //sepChain.remove(k);
                        break;
                    case 7: /*bookHash.removeAny()*/;
                }
            }
            //stops timer
            timer1.stop();
            //records stats
            stats[i].record(timer1);
            }
        } // end of trials loop

        for (int i = 0; i < number_of_algorithms; ++i)
        {
            //outputs results console
            stats[i].report(cout);
            //outputs results to file
            stats[i].report(ofs);
        }

        cout << endl;
        ofs << endl;
        //set current size to old size to mark starting point for adding more values to vetor

        old_size = current_size;
        //multiply the number of elements to be tested by "INCREMENT_FACTOR"
        current_size *= INCREMENT_FACTOR;
        for (unsigned int m = old_size; m < current_size; ++m) {
            //fill the rest of the vector to current_size starting at the old size
            testVector.push_back(rand());
            //fill the rest of the keyvector
            keyVector.push_back(testVector[m]%101);
        }
    }
    return 0;
}
