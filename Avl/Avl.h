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

        Avl(string value);

        friend Avl* Insert_Avl(Avl* Avl_node, string word);
        friend Avl* Delete_Avl(Avl* Avl_node, string word);
        friend Avl* Search_Avl(Avl* node,string word);
        friend Avl *R_Rotation(Avl *rot_node);
        friend Avl *L_Rotation(Avl *rot_node);
        friend int Bal_calc(Avl *node);
        friend int get_height(Avl *node);
        friend int max(int a, int b);

        friend void preorder(Avl *root);
        friend void postorder(Avl *root);
        friend void inorder(Avl *root);


        string getValue() {return value;}
        int getDuplicates() {return duplicates;}

    private:
        string value;
        Avl *Left;
        Avl *Right;
        int duplicates;
        int height;


};
#endif // AVL_H
