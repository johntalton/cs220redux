#ifndef MINMAXHEAP_H
#define MINMAXHEAP_H
#include <iostream.h>

template <class Type> class MinMaxHeap;


template <class Type>
class Node{
   friend class MinMaxHeap <Type>;
   public:
      Node();
   private:
      Node *Left;
      Type data;
      Node *Right;
};

template <class Type> 
Node<Type>::Node(){ Left=0; Right=0; }

template <class Type>
class MinMaxHeap{
   public:
     MinMaxHeap(int MinorMax);
     void print_Heap(ostream& o);
     void Add(Type value);


   private:
      void print(ostream& o, Node<Type>* N, int indent);
      int isMin;
      Node<Type> *root;
};
#endif

template <class Type>
MinMaxHeap<Type>::MinMaxHeap(int MinorMax){
   isMin = MinorMax;
   root = 0;
}

///////////////////////////////////////
// this stuff prints the Heap
template <class Type>
ostream& operator<< (ostream& os, MinMaxHeap<Type> b){
   b.print_Heap(os);
   return os;
}  
template <class Type>
void MinMaxHeap<Type>::print_Heap(ostream& o){ print(o,root,0); }
template <class Type>
void MinMaxHeap<Type>::print(ostream& o, Node<Type>* N, int indent){
   if(N)
   {
   print(o, N->Right, indent + 1);
   for(int i = 0; i < indent; i++) { o << "   "; }
   o << N->data << endl;
   print(o, N->Left, indent + 1);
   }
}
///////////////////////////////////////
// end of stuff to print heap
///////////////////////////////////////


template <class Type>
void MinMaxHeap<Type>::Add(Type value){
   Node<Type> *TempNode = new Node<Type>();
   Node<Type> *P;
   
   TempNode->data = value;
   
   
   
   P = TempNode;
   root = P;

}