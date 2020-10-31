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
using namespace std;
using namespace std::chrono;


string clear(string word)
{
    char chars[] = " ()~`<>.'!@#$%^&*-_+=:\",/|{}[]:;? " ;                      //Clear function that when given a string parameter
    for (unsigned int i=0; i<strlen(chars); i++)                                // returns the string without any special symbols.
        word.erase(std::remove(word.begin(), word.end(), chars[i]), word.end());
    return word;
}

string* resize(string* &array,int &capacity)
{
    string *temp;
    temp = new string [capacity+2500];                                          //Resize function that takes as parameters by reference
                                                                                //a string array and its capacity.Tries to allocate a new
    if (temp)                                                                   //array of string of size (array+2500).If not possible (temp==null)
        {                                                                       //prints a message and just returns null.
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


/*
The assingment was to open a .txt file and read all the words (clear from special symbols)
of the file. After that we had to create 3 different data structures and store all the words.
Also we had to pick a random amount of wards to search in the data structures to see how
efficient they are. We implemented that by always picking 1/3 of the amount of total unique words
but the trick was the 1/3 of words were always random. In the meantime we had to time the search
process for every datastructure. In the end we were asked to print all the search words and their
duplicates αs well as the time it took each structure to search for the words.
*/


int main()
{
    // filestream variable file
    ifstream infile;
    ofstream outfile;
    string let;
    string filename;

    string *words,*hashwords,*searchwords;                                      //Pointers for the creation of string arrays.

    int k=0,j=0;                                                                //counters.

    int capacity1 = 5000,capacity2 = 5000;                                      //Initial capacities of *hashwords* and *words*
                                                                                //arrays.

    words = new string [capacity1];                                             //Initialization
    hashwords = new string [capacity2];


    Tree *bst_root = NULL;                                                      //Creating the structures
    Avl *avl_root = NULL;
    HashTable *table = NULL;

    filename = "file.txt";                                                      //filename of the file doc

    infile.open(filename.c_str());                                              //open txt and load text to file

    cout<<"Inserting all the words to the structures..."<<endl<<endl<<endl;

    //STRUCTURES INSERΤION
    while (infile >> let)
    {
      let = clear(let);                                                       //Clearing the word from symbols
      if ( !Search(bst_root, let) )                                           //If not in BST then it's a new word
        {
          if (k >= capacity1)
            {
              words = resize(words,capacity1);
            }
          words[k]=let;                                                   //Array of unique words with resize function
          k++;
        }
      if (j >= capacity2)
        {
          hashwords = resize(hashwords,capacity2);                        //Array of total words with resize function
        }
      hashwords[j]=let;
      j++;

      bst_root = Insert(bst_root,let);                                        //Inserting all the words to the trees
      avl_root = Insert_Avl(avl_root,let);
    }

    infile.close();

    table = new HashTable( k );                                                 //Initialization of dynamic HashTable

    for (int i=0; i<j ; i++)
      {
        table->InsertValue(hashwords[i]);                                   //Inserting total words to HashTable
      }

    cout<<"Total words :"<<j<<"\t||\t"<<"Unique words: "<<k<<endl<<endl<<endl;
    cout<<"Creating the string array for Searching."<<endl;

    searchwords = new string [k];                                               //Construction of a random-word table for Search in structures
    int l=0;
    srand (time(NULL));

    for(int i=0;i<k;i++)
      {
      if (rand() %3 == 1)
        {
          searchwords[l] = words[i];                                          //Getting random 1/3 of the unique words of text
          l++;
        }
      }

    cout<<"Constructed an array with: "<<l<<"  random words "<<endl<<endl;

    outfile.open("results.txt");                                                //Opening results.txt to print our results

    cout<<"Searching...\t[Binary Search Tree]"<<endl;
    outfile<<"======="<<endl<<"RESULTS"<<endl<<"======="<<endl<<endl;


/*
  Basically we stored all the unique words of the file.txt in the *words* array
all the words in general in the *hashwords* array and at the end all the words
that we are going to search for in the *searchwords* array. Following that
we searched all the Data Structures in order, timing them on searching time
efficiency proving amazing results for all of them! After gathering the searching
times we printed them in the results.txt file to see how they executed.
*/



    //1.BST SEARCH
    auto start_bst = high_resolution_clock::now();

    for (int i=0; i<l ; i++)
        {
          Search(bst_root,searchwords[i]);
        }

    auto stop_bst = high_resolution_clock::now();
    auto duration_bst = duration_cast<nanoseconds>(stop_bst - start_bst);
    outfile<<"Duration of BST Search: "<<duration_bst.count()<<"  nanoseconds"<<endl;  //Printing the results

    cout<<"Searching...\t[Avl Search Tree]"<<endl;

    //2.AVL SEARCH
    auto start_avl = high_resolution_clock::now();

    for (int i=0; i<l ; i++)
        {
          Search_Avl(avl_root,searchwords[i]);
        }

    auto stop_avl = high_resolution_clock::now();
    auto duration_avl = duration_cast<nanoseconds>(stop_avl - start_avl);
    outfile<<"Duration of AVL Search: "<<duration_avl.count()<<"  nanoseconds"<<endl;  //Printing the results

    cout<<"Searching...\t[Open Addressing Hash Table]"<<endl;
    //3.HASH SEARCH
    auto start_hash = high_resolution_clock::now();

    for (int i=0;i<=l;i++)
        {
          table->SearchValue(searchwords[i]);
        }

    auto stop_hash = high_resolution_clock::now();
    auto duration_hash = duration_cast<nanoseconds>(stop_hash - start_hash);
    outfile<<"Duration of Hash Table Search: "<<duration_hash.count()<<"  nanoseconds"<<endl; //Printing the results


    /*
      After that we were asked to print all the words that we searched
    for with their duplicates.That was in order to really see if we saved
    the words correctly and if we implemented the structures correctly.
    Prefered to use BST,without a specific reason why :D
    */

    outfile<<endl<<endl<<endl<<"=============="<<endl<<"SEARCHED WORDS"<<endl<<"=============="<<endl<<endl;

    outfile<<"Words searched: "<<l<<endl<<endl;


    //PRINTING ALL THE SEARCH WORDS WITH THEIR DUPLICATES
    for (int i=0; i<l ; i++)
        {
            if(!Search(bst_root,searchwords[i]))
                outfile<<i+1<<") Did not find the word: "<<searchwords[i]<<endl;
            else
                outfile<<i+1<<") Found the word: "<<searchwords[i]<<"\t\t with ["<<Search(bst_root,searchwords[i])->getDuplicates()<<"] duplicates."<<endl;
        }

    outfile.close();
    cout<<endl<<"Results have been written in the results.txt file. Please go check it out!"<<endl<<endl<<"Thank you!"<<endl;



    return 0;
}
