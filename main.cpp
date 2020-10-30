#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include "Tree.h"
#include "Avl.h"
#include "HashTable.h"
#include "HashTable.h"
#include "Print.h"
#define COUNT 8

using namespace std;
using namespace std::chrono;


string clear(string word)
{
    char chars[] = " ()~`<>.'!@#$%^&*-_+=:\",/|{}[]:;? " ;
    for (unsigned int i=0; i<strlen(chars); i++)
        word.erase(std::remove(word.begin(), word.end(), chars[i]), word.end());
    return word;
}

string* resize(string* &array,int &capacity)
{
    string *temp;
    temp = new string [capacity+2500];

    if (temp)
        {

            for (int i=0; i<capacity ; i++)
                {
                        temp[i] = array[i];
                }
            delete[] array;
            capacity+=2500;
            return temp;

        }
    else
        cout<<"Not enough space to resize array..."<<endl;
    return temp;
}

int main()
{
    // filestream variable file
    ifstream infile;
    ofstream outfile;
    string let;
    string filename;
    string *words,*hashwords,*searchwords;


    int k=0,j=0;   //counters



    int capacity1 = 5000,capacity2 = 5000;


    words = new string [capacity1];
    hashwords = new string [capacity2];




    //creating the structures
    Tree *root = NULL;
    Avl *root1 = NULL;
    HashTable *table = NULL;

    //filename of the file doc
    filename = "file.txt";

    //open txt and load text to file
    infile.open(filename.c_str());



    cout<<"Inserting all the words to the structures..."<<endl<<endl<<endl;


    //STRUCTURES INSERTION
    while (infile >> let)
    {

        let = clear(let);                       //Clearing the word from symbols


        if ( !Search(root, let) )           //If not in BST then it's a new word
            {
                if (k >= capacity1)
                    {
                        words = resize(words,capacity1);
                    }
                words[k]=let;                        //Array of unique words with resize function
                k++;

            }

        if (j >= capacity2)
            {
                hashwords = resize(hashwords,capacity2);            //Array of total words with resize function
            }

        hashwords[j]=let;
        j++;


        root = Insert(root,let);            //Inserting all the words to the trees
        root1 = insert_avl(root1,let);




    }

    infile.close();



    table = new HashTable( k );         //Initialization of dynamic HashTable


    for (int i=0; i<j ; i++)
        {
            table->InsertValue(hashwords[i]);           //Inserting total words to HashTable
        }


    cout<<"Total words :"<<j<<"\t||\t"<<"Unique words: "<<k<<endl<<endl<<endl;

    cout<<"Creating the string array for Searching."<<endl;
    //Construction of a random-word table for Search in structures
    searchwords = new string [k];
    int l=0;
    srand (time(NULL));

    for(int i=0;i<k;i++)
    {
        if (rand() %3 == 1)
        {
            searchwords[l] = words[i];   //getting random 1/3 of the unique words of text

            l++;
        }
    }

    cout<<"Constructed an array with: "<<l<<"  random words "<<endl<<endl;


    outfile.open("results.txt");



    cout<<"Searching...\t[Binary Search Tree]"<<endl;
    outfile<<"======="<<endl<<"RESULTS"<<endl<<"======="<<endl<<endl;


    //1.BST SEARCH
    auto start_bst = high_resolution_clock::now();

    for (int i=0; i<l ; i++)
        {
            Search(root,searchwords[i]);

        }

    auto stop_bst = high_resolution_clock::now();
    auto duration_bst = duration_cast<nanoseconds>(stop_bst - start_bst);
    outfile<<"Duration of BST Search: "<<duration_bst.count()<<"  nanoseconds"<<endl;


    cout<<"Searching...\t[Avl Search Tree]"<<endl;
    //2.AVL SEARCH
    auto start_avl = high_resolution_clock::now();

    for (int i=0; i<l ; i++)
        {
            search_avl(root1,searchwords[i]);
        }

    auto stop_avl = high_resolution_clock::now();
    auto duration_avl = duration_cast<nanoseconds>(stop_avl - start_avl);
    outfile<<"Duration of AVL Search: "<<duration_avl.count()<<"  nanoseconds"<<endl;

    cout<<"Searching...\t[Open Addressing Hash Table]"<<endl;
    //3.HASH SEARCH
    auto start_hash = high_resolution_clock::now();

    for (int i=0;i<=l;i++)
    {
        table->SearchValue(searchwords[i]);
    }

    auto stop_hash = high_resolution_clock::now();
    auto duration_hash = duration_cast<nanoseconds>(stop_hash - start_hash);
    outfile<<"Duration of Hash Table Search: "<<duration_hash.count()<<"  nanoseconds"<<endl;

    outfile<<endl<<endl<<endl<<"=============="<<endl<<"SEARCHED WORDS"<<endl<<"=============="<<endl<<endl;

    outfile<<"Words searched: "<<l<<endl<<endl;


    //PRINTING ALL THE SEARCH WORDS WITH THEIR DUPLICATES
    for (int i=0; i<l ; i++)
        {
            if(!Search(root,searchwords[i]))
                outfile<<i+1<<") Did not find the word: "<<searchwords[i]<<endl;
            else
                outfile<<i+1<<") Found the word: "<<searchwords[i]<<"\t\t with ["<<Search(root,searchwords[i])->getDuplicates()<<"] duplicates."<<endl;
        }

    outfile.close();
    cout<<endl<<"Results have been written in the results.txt file. Please go check it out!"<<endl<<endl<<"Thank you!"<<endl;



    return 0;
}


