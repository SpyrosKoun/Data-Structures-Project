#ifndef HASHTABLE_H
#define HASHTABLE_H
#include<iostream>
#include<algorithm>
#include<fstream>
#include <cstring>
#include <string>
#include "Cell.h"

using namespace std;


class HashTable
{
    public:
        HashTable(int i);
        ~HashTable();

        void InsertValue (string word);
        void SearchValue (string word);
        bool IsEmpty(int i);
        void PrintHash();


        unsigned long int HashFunction (string word);

        int Getwordcount() {return wordcount;}


    protected:

    private:
        Cell **HashMap;
        int wordcount;
        int size;

};

#endif // HASHTABLE_H
