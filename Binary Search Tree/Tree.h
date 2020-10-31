#ifndef TREE_H
#define TREE_H
#include <cstring>
#include <string>


using namespace std;
class Tree
{
    public:


        friend Tree* Insert(Tree* node,string word);
        friend Tree* Delete(Tree* node,string word);
        friend Tree* Search(Tree* node,string word);
        friend Tree* Inorder_successor(Tree* node);

        friend void preorder(Tree *root);
        friend void postorder(Tree *root);
        friend void inorder(Tree *root);

        string getValue() {return value;}
        int getDuplicates() {return duplicates;}

    private:
        Tree *Left;
        Tree *Right;

        string value;

        int duplicates;

};

#endif // TREE_H
