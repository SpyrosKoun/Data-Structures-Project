#include "Avl.h"
#include<iostream>
#include<algorithm>
#include<fstream>
#include <cstring>
#include <string>

using namespace std;


Avl::Avl(string value)
{
  this.value = value;
  Left = NULL;  //creates children
  Right = NULL;
  height = 1;   //sets height of new obj to 1
  duplicates=1; //sets dublicates counter to 1
}

Avl* Insert_Avl(Avl* Avl_node, string word)
{
    if (Avl_node == NULL)   //Node is empty
    {
        Avl* node = new Avl(word); //creates a pointer to a new Avl obj
        return(node);       //returns a pointer to obj that just created
    }

    if (word < Avl_node->value)
        Avl_node->Left = insert_avl(Avl_node->Left, word);      //Moving to the left child
    else if (word > Avl_node->value)
        Avl_node->Right = insert_avl(Avl_node->Right, word);    //Moving to the right child
    else if (word == Avl_node->value)
        Avl_node->duplicates++;                                 //Word already exists. So duplicates++
    else
        return Avl_node;

    //Update height of this ancestor Avl
    Avl_node->height = 1 + max( get_height(Avl_node->Left) , get_height(Avl_node->Right) );


    //balance factor of this  Avl node to check if this Avl became unbalanced


    int balance = Bal_calc(Avl_node); // in case avl balance has become >= |2| -> 4 cases

    // left-left Case
    if (balance > 1 && word < Avl_node->Left->value)
        return R_Rotation(Avl_node);

    // right-right Case
    if (balance < -1 && word > Avl_node->Right->value)
        return L_Rotation(Avl_node);

    // left-right Case
    if (balance > 1 && word > Avl_node->Left->value)
    {
        Avl_node->Left = L_Rotation(Avl_node->Left);
        return R_Rotation(Avl_node);
    }

    // right-left Case
    if (balance < -1 && word < Avl_node->Right->value)
    {
        Avl_node->Right = R_Rotation(Avl_node->Right);
        return L_Rotation(Avl_node);
    }

    //return the (unchanged) Avl_node pointer ( new Avl_node of the subtree for recursion)
    return Avl_node;
}


Avl* Search_Avl(Avl* node, string word)
{
    if ( node == NULL )
        return node ;                   //Searched through the path of the node and did not find it
    if (node->value == word)
            return node;                       //Found the word
    if (node->value < word)
       return Search_Avl(node->Right, word);    //Moving to right child

    return Search_Avl(node->Left, word);        //Moving to left child
}



Avl* Delete_Avl(Avl* Avl_node, string word)
{


    if (Avl_node == NULL)           //Did not find the word
        return Avl_node;

    if ( word < Avl_node->value )       //Moving to the left child
        Avl_node->Left = Delete_Avl(Avl_node->Left, word);
    else if( word > Avl_node->value )   //Moving to the right child
        Avl_node->Right = Delete_Avl(Avl_node->Right, word);

    // Found the word i want to delete
    else
    {
        // Node has 2 children
        if( (Avl_node->Left != NULL) && (Avl_node->Right != NULL) )
        {

            // if node with two children fetch smallest of right subtree
            Avl* temp = Avl_node->Right;
            while (temp->Left != NULL)
                temp = temp->Left; //most left of right subtree

            // Copy most left value to this node
            Avl_node->value = temp->value;

            // Delete used most left of right subtree (return deleted subtree to right pointer)
            Avl_node->Right = Delete_Avl(Avl_node->Right, temp->value);
        }
        else //0 or 1 child
        {
            //place in temp NULL or the child that has value
            Avl *temp = Avl_node->Left;
            if (Avl_node->Right)
            {
                temp= Avl_node->Right;
            }

            if (temp == NULL)  // 0 children
            {
                temp = Avl_node;
                Avl_node = NULL;
            }
            else // 1 child
                *Avl_node = *temp; // Replace Avl_node with the contents of the child that has value

            free(temp);  //delete temp pointer
        }
    }

    //return if only root exists after delete
    if (Avl_node == NULL)
        return Avl_node;



    // update height of this node
    Avl_node->height = 1 + max(get_height(Avl_node->Left), get_height(Avl_node->Right));

    // check balance to know if this node is unbalanced
    int balance = get_height(Avl_node->Left) - get_height(Avl_node->Right);

    // If this node isunbalanced then:

    // Left Left
    if (balance > 1 && Bal_calc(Avl_node->Left) >= 0)
        return R_Rotation(Avl_node);

    // Right Right
    if (balance < -1 && Bal_calc(Avl_node->Right) <= 0)
        return L_Rotation(Avl_node);

    // Left Right
    if (balance > 1 && Bal_calc(Avl_node->Left) < 0)
    {
        Avl_node->Left = L_Rotation(Avl_node->Left);
        return R_Rotation(Avl_node);
    }

    // Right Left
    if (balance < -1 && Bal_calc(Avl_node->Right) > 0)
    {
        Avl_node->Right = R_Rotation(Avl_node->Right);
        return L_Rotation(Avl_node);
    }

    return Avl_node;
}





Avl *R_Rotation(Avl *rot_node)
{
    //rot_node is the node to be rotated
    Avl *top = rot_node->Left; //new node to become top
    Avl *temp = top->Right;

    // Perform rotation
    top->Right = rot_node;
    rot_node->Left = temp;

    // Update heights
    rot_node->height = max( get_height(rot_node->Left) , get_height(rot_node->Right) ) + 1;

    top->height = max( get_height(top->Left) , get_height(top->Right) ) + 1;

    // Return new Avl_node
    return top;
}


Avl *L_Rotation(Avl *rot_node)   //     rot_node
{                                //        \.
    Avl *top = rot_node->Right;  //          \.
    Avl *temp = top->Left;      //           1.(rot_node)Right -> (top)     rot_node(after rotation)
                                //               /     \.
    // Perform rotation        //               /       \.
    top->Left = rot_node;      //   2.(top)Left->temp   .........
    rot_node->Right = temp;    //   3.rot_node->(top)Left(after rotation)
                               //   4.temp->(rot_node)Right(after rotation)
    // Update heights
    rot_node->height = max( get_height(rot_node->Left) , get_height(rot_node->Right) ) + 1;
    top->height = max( get_height(top->Left), get_height(top->Right)) + 1;

    // Return new Avl_node
    return top;
}

int Bal_calc(Avl *node)
{
    if (node == NULL)
        return 0;
    return get_height(node->Left) - get_height(node->Right);
}
//get the height of the tree
int get_height(Avl *node)
{
    if (node == NULL)  //In case node is only created
        return 0;
    return node->height;
}


int max(int a, int b)
{
    if (a>b)
        return a;
    else
        return b;
}


void postorder(Avl *root)
{
    if (root != NULL)
    {
        postorder(root->Left);                  // First visiting the left child then the right child and in the end the root
        postorder(root->Right);
        cout<<root->value<<endl;
    }
}


void preorder(Avl *root)
{
    if (root != NULL)
    {
        cout<<root->value<<endl;
        preorder(root->Left);                   // First visiting the root then the left child and in the end the right child
        preorder(root->Right);
    }
}


void inorder(Avl *root)
{
    if (root != NULL)
    {
        inorder(root->Left);
        cout<<root->value<<endl;                // First visiting the left child then the root and in the end the right child
        inorder(root->Right);
    }
}
