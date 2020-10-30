#ifndef AVL_H
#define AVL_H
#include<iostream>
#include<algorithm>
#include<fstream>
#include <cstring>
#include <string>

using namespace std;

class Avl
{
    public:

        friend Avl* insert_avl(Avl* Avl_node, string word);
        friend Avl* delete_avl(Avl* Avl_node, string word);
        friend Avl* search_avl(Avl* node,string word);
        friend Avl *R_Rotation(Avl *rot_node);
        friend Avl *L_Rotation(Avl *rot_node);
        friend int Bal_calc(Avl *node);
        friend int get_height(Avl *node);
        friend int max(int a, int b);


        string getValue() {return value;}
        int getDuplicates() {return duplicates;}
        Avl* getRight() {return Right;} //for print2d
        Avl* getLeft() {return Left;}  //for print2d

    private:
        string value;
        Avl *Left;
        Avl *Right;
        int duplicates;
        int height;


};
#endif // AVL_H
