#ifndef BTREE_H
#define BTREE_H
#include <string.h>


//Small substring fulction used by Make tree
char* SubStr(char thestr[],int from, int to)
{
   int len = to - from + 1;
   char *str = new char[len+1];
   int a = 0;
   for(int i = from; i <= to; i++){
      str[a++] = thestr[i];
   }
   str[a] = '\0';
   return str;
}

//BTree Node
template <class Type> class BTree;

template <class Type>
class TreeNode{
   friend class BTree <Type>;
   private:
      TreeNode *Left;
      Type data;
      TreeNode *Right;
};
/*
This is a bianary tree
*/
template <class Type>
class BTree{
   public:
     BTree();
     void MakeTree(char* IO, char* PO);
     TreeNode<char>* MakeT(TreeNode<char>* T,char* IO, char* PO);
     void print_Tree(ostream& o);
     void print(ostream& o, TreeNode<Type>* N, int indent);
     void PreOrder();
     void PostOrder();
     void InOrder();
     void PreOrder(TreeNode<char> *C);
     void PostOrder(TreeNode<char> *C);
     void InOrder(TreeNode<char> *C);
   private:
      TreeNode<Type> *root;
};
#endif

template <class Type>
void BTree<Type>::PreOrder(){ PreOrder(root); }

template <class Type>
void BTree<Type>::PreOrder(TreeNode<char> *C)
{
   if(C){
      cout << C->data;
      PreOrder(C->Left);
      PreOrder(C->Right);
   }
}
template <class Type>
void BTree<Type>::PostOrder(){ PostOrder(root); }

template <class Type>
void BTree<Type>::PostOrder(TreeNode<char> *C)
{
   if(C){
      PostOrder(C->Left);
      PostOrder(C->Right);
      cout << C->data;
   }
}
template <class Type>
void BTree<Type>::InOrder(){ InOrder(root); }

template <class Type>
void BTree<Type>::InOrder(TreeNode<char> *C)
{
   if(C){
      InOrder(C->Left);
      cout << C->data;
      InOrder(C->Right);
   }
}
template <class Type>
ostream& operator<< (ostream& os, BTree<Type> b){
   b.print_Tree(os);
   return os;
  }


template <class Type>
BTree<Type>::BTree()
{
   root = 0;
}

template <class Type>
void BTree<Type>::print_Tree(ostream& o)
{
   print(o,root,0);
}

template <class Type>
void BTree<Type>::print(ostream& o, TreeNode<Type>* N, int indent)
{
   if(N)
   {
   print(o, N->Right, indent + 1);
   for(int i = 0; i < indent; i++) { o << "   "; }
   o << N->data << endl;
   print(o, N->Left, indent + 1);
   }
}


template <class Type>
void BTree<Type>::MakeTree(char IO[], char PO[])
{
  root = new TreeNode<char>();
  root = MakeT(root,IO,PO);

}


template <class Type>
TreeNode<char>* BTree<Type>::MakeT(TreeNode<char>* T,char IO[], char PO[])
{
   if(strlen(IO) == 0) { return 0; }
   else
   {
        int split = -1;
        T = new TreeNode<char>();
        T->data = *SubStr(PO,strlen(PO) -1 ,strlen(PO)-1);
        while((IO[split] != T->data) && (split != strlen(IO))){ split++; }
        T->Left =  MakeT(T->Left,  SubStr(IO,0,split-1),          SubStr(PO,0,split-1));
        T->Right = MakeT(T->Right, SubStr(IO,split+1,strlen(IO)-1), SubStr(PO, split, strlen(PO)-1-1));
        return T;
   }
}