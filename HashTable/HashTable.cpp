#include "HashTable.h"
#include<iostream>
#include<algorithm>
#include<fstream>
#include <cstring>
#include <string>
#include "Cell.h"
using namespace std;


//Constructor
HashTable::HashTable(int i)
{
    HashMap= new Cell *[2*i];                                                   //Creating an array of Cell pointers with twice the size of unique
                                                                                //words and setting them all to NULL.Also setting the size and the wordcount
    for (int j=0 ; j<2*i; j++)
        HashMap[j] = NULL;
    size=2*i;
    wordcount=0;
}


HashTable::~HashTable()
{
    for (int i=0; i<size ; i++)                                                 //Deleting all the HashMap entries and the the HashMap itself
        delete HashMap[i];
    delete[] HashMap;

}


unsigned long int HashTable::HashFunction( string word )
{
    unsigned long hash = 5381;                                                  //This is Djb2's function for calculating a very unique HashMap key
    unsigned int length  = word.length();                                       //for every word that is entered.
    unsigned int i = 0;

    for (i = 0; i < length ; i++)
    {
        hash = ((hash << 5) + hash) + (word[i]);
    }


    return hash % size;
}


void HashTable::InsertValue( string word )
{
    unsigned long int k;                                                        //Key for the word we want to insert
    unsigned long int Start;                                                    //First key that the word was assigned
    bool flag = false;

    k = HashFunction(word);                                                     //Calculating the key for the given word
    Start = k;

    do
    {
            if ( HashMap[k] == NULL )
            {
                HashMap[k] = new Cell(word);                                    //Found an empty cell in the HashMap[k] position
                flag=true;                                                      //so we insert the word.
            }
            else if ( HashMap[k]->Getword() == word)
            {
                HashMap[k]->Setduplicates( HashMap[k]->Getduplicates() + 1 );   //Found the same word as the one we trying to insert.
                break;                                                          //So incrementing duplicates.
            }
            else
            {
                    k = (k + 1) % this->size;                                   //Cell occupied.Going to the next cell...
            }
    }
    while ( flag == false && Start != k);                                       //Full circle or found a cell to put the word

    wordcount++;                                                                //Incrementing wordcount




}


void HashTable::SearchValue ( string word )
{
    unsigned long int k;                                                        //Key for the word we want to insert
    unsigned long int Start;                                                    //First key that the word was assigned
    bool flag = false;

    k = HashFunction(word);                                                     //Calculating the key for the given word
    Start = k;

    do
    {

        if ( HashMap[k] != NULL)                                                //Found an non-empty cell. Checking if it has our word
        {

            if ( HashMap[k]->Getword() == word)                                 //It has our word so we end the loop
                flag = true;
            else
                k = (k + 1) % this->size;                                       //Does not have our word.. Going to the next cell

        }
        else
            k = (k + 1) % this->size;                                           //Found an empty cell so i am going to the next cell



    }
    while ( flag == false && Start != k );                                      //All that until I find my word or I make a full circle


}


bool HashTable::IsEmpty(int i)
{
    if (HashMap[i] != NULL)                                                     //Given a specific key, check if that cell is empty or not
        {
            cout<<HashMap[i]->Getword()<<" "<<HashMap[i]->Getduplicates()<<endl;
            return false;                                                       //Not empty
        }
    return true;                                                                //Empty

}


void HashTable::PrintHash()
{
                                                                                //Printing the whole HashMap
    for (int i=0; i <size ; i++)
        if (HashMap[i] != NULL)
            cout<<"["<<i<<"] "<<HashMap[i]->Getword()<<" \t| Duplicates: "<<HashMap[i]->Getduplicates()<<endl;

}
