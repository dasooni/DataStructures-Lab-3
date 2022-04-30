#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cassert>  //assert

#include "BinarySearchTree.h"

#define TEST_EXERCISE3

/* *********************************************
 * Exercise 3: frequency table
 ********************************************* */

#ifdef TEST_EXERCISE3

struct Row {
    // ADD CODE: exercise 3
    std::string key;       
    int value = 0;

    bool operator<(const Row& other) const {
        return key < other.key;
    }

};
// Add other stuff, if needed
bool hasChar(char c) {
    std::string wrongChar = ".,!?:\"();";       //Forbidden chars

    if ((std::find(wrongChar.begin(), wrongChar.end(), c)) != wrongChar.end()) { //If c is NOT "wrongChar", return false. 
        return false;
    }
    return true;        //If c is "wrongChar", return true
}

std::string convertWord(std::string word) {     //Converts the word into correct format
    std::string correctWord;

    std::transform(word.begin(), word.end(), word.begin(), ::tolower);              //Transform all letters to lowercase
    std::copy_if(word.begin(), word.end(), back_inserter(correctWord), hasChar);    //copy chars into "correctWord" depending on "hasChar()"

    return correctWord;
}

#endif

void exercise3() {
#ifdef TEST_EXERCISE3
    {
        std::ifstream file(".../code/text.txt");  // contains 56 unique words
        //std::ifstream file("C:.../code/text_long.txt"); // contains 497 unique words

        if (!file) {
            std::cout << "Couldn't open file text.txt\n";
            // std::cout << "Couldn't open file text_long.txt\n";
            return;
        }

        // ADD CODE: exercise 3
        BinarySearchTree<Row> t;
        std::string word;           
        
        while (file >> word) {      //store every word in file into "word"
            Row row;                
            row.key = convertWord(word);    //convert the word to correct standard.
            BinarySearchTree<Row>::Iterator it = t.find(row);   //Check if row is in t. If find, points to it. If not, points to t.end().
            if (it == t.end()) {            //create new row if not find
                row.value = 1;              
                t.insert(row);              //insert the row
            }
            else it->value++;               //If it was find, increase "value"
        }
      
        
        /* *********************************************
            * Print out freq_table. Check if it's correct *
            ********************************************* */

       /* BinarySearchTree<Row>::Iterator it = t.begin();
        while (it != t.end()) {
            std::cout << it->value << "\t" << it->key << std::endl;
            ++it;
        }*/

    }
	assert(BinarySearchTree<Row>::get_count_nodes() == 0);

    std::cout << "Success!!\n";
#endif		
}
