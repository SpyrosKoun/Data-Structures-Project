#ifndef CELL_H
#define CELL_H
#include<iostream>
#include<algorithm>
#include<fstream>
#include <cstring>
#include <string>

using namespace std;

//This class was used to create Cell objects that were
//later would be used as HashTable Entries

class Cell
{
    public:
        /** Default constructor */
        Cell(string word);

        void deleteWord() {word.clear();}
        void deleteDuplicates() {duplicates =0;}

        string Getword() { return word; }
        int Getduplicates() { return duplicates; }

        void Setword(string val) { word = val; }
        void Setduplicates(int val) { duplicates = val; }

    protected:

    private:
        string word;
        int duplicates;
};

#endif // CELL_H
