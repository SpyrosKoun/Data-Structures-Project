#include "Tree.h"
#include<iostream>
#include<algorithm>
#include<fstream>
#include <cstring>
#include <string>

using namespace std;



Tree* Insert(Tree* node, string word)
{
    if (node == NULL)
            {
                Tree *node = new Tree();
                node-> Left = NULL;
                node-> Right = NULL;
                node-> value = word;                //Creating a new node and saving the word to value
                node-> duplicates = 1;
                return node;
            }
    else if (node->value == word)
        node-> duplicates++;                        //Increasing duplicates
    else if (word < node->value)
            node->Left = Insert(node->Left, word);  //Moving to left child

    else if (word > node->value)
        node->Right = Insert(node->Right, word);    //Moving to right child
    return node;
}



Tree* Search(Tree* node, string word)
{
    if ( node == NULL )
        return node ;                   //Searched through the path of the node and did not find it
    if (node->value == word)
            return node;                       //Found the word
    if (node->value < word)
       return Search(node->Right, word);    //Moving to right child

    return Search(node->Left, word);        //Moving to left child
}




Tree* Inorder_successor(Tree* node)
{
    Tree* temp = node;                      //Initialization of temporary node

    while (temp && temp->Left != NULL)     //Trying to find the inorder succesor
        temp = temp->Left;

    return temp;
}

Tree* Delete(Tree* node, string word)
{
    //Searched through the path of the node and did not find it
    if (node == NULL) return node;

    if (word < node->value)
        node->Left = Delete(node->Left, word);      //Moving to left child

    else if (word > node->value)
        node->Right = Delete(node->Right, word);    //Moving to right child

    //Found the node
    else
    {
        // First case : one or no child
        if (node->Left == NULL)
        {
            Tree *temp = node->Right;
            delete node;
            return temp;
        }
        else if (node->Right == NULL)
        {
            Tree *temp = node->Left;
            delete node;
            return temp;
        }

        // Second case : two children. Finding the inorder succesor...
        Tree* temp = Inorder_successor(node->Right);

        // Coping the inorder successor's content to node
        node->value = temp->value;
        node->Left = temp->Left;
        node->Right = temp->Right;
        node->duplicates = temp->duplicates;

        // Delete the inorder successor
        node->Right = Delete(node->Right, temp->value);
    }
    return node;            //Returning the node
}


void postorder(Tree *root)
{
    if (root != NULL)
    {
        postorder(root->Left);                  // First visiting the left child then the right child and in the end the root
        postorder(root->Right);
        cout<<root->value<<endl;
    }
}


void preorder(Tree *root)
{
    if (root != NULL)
    {
        cout<<root->value<<endl;
        preorder(root->Left);                   // First visiting the root then the left child and in the end the right child
        preorder(root->Right);
    }
}


void inorder(Tree *root)
{
    if (root != NULL)
    {
        inorder(root->Left);
        cout<<root->value<<endl;                // First visiting the left child then the root and in the end the right child
        inorder(root->Right);
    }
}
