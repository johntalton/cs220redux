#ifndef LIST_H
#define LIST_H

template <class Type> class List;

template <class Type> class ListNode 
{
   friend class List <Type>; 
   public:
      ListNode(Type val){
         data = val;
         link = 0;
      }
   private:
      Type data;
      ListNode *link;
};

template <class Type>
class List 
{
   public:
      List() {first = 0;}; // constructor
      void Insert(Type item); // insert an element in the ordered list
      Type *Delete(); // delete the head node
      bool IsEmpty(){
         if(first)   return false;
         else return true;
      }
   private:
      ListNode <Type> *first;
};
#endif


template <class Type>
void List<Type>::Insert(Type item) 
{
   ListNode <Type>*NewNode = new ListNode<Type>(item);
   ListNode <Type> *p = first;
   ListNode <Type> *q = 0;
   if(first == 0){ first = NewNode; }
   else
   {
      while((p != 0) && (NewNode->data > p->data)){
         q = p;
         p = p->link;   
      }
      NewNode->link = p;
      if(q != 0) { q->link = NewNode; } else { first = NewNode; }
   }
}

template <class Type> 
Type *List<Type>::Delete() 
{
   if(first){
      ListNode <Type> *p = first;
      first = first->link;
      return &p->data;
   }
   cout << "Error... cannot delete from empty list";
   return 0;
}