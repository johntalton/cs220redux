//John Talton
//cs220 - stack.h
//4/8/98
#ifndef _stack_h
#define _stack_h
#include <iostream.h>

#define DefaultSize 100


template <class KeyType>
class Stack
{
   public:
      Stack(int MaxStackSize = DefaultSize);
      int IsFull();
      int IsEmpty();
      void Add(const KeyType& item);
      KeyType* Delete(KeyType&);
      int suppresserrors;
    private:
      void StackFull();
      void StackEmpty();
      int top;
      KeyType *stack;
      int MaxSize;
};
#endif

template <class KeyType>
Stack<KeyType>::Stack(int MaxStackSize):MaxSize (MaxStackSize)
{
   suppresserrors = 0;
   stack = new KeyType[MaxSize];
   top = -1;
}

template <class KeyType>
inline int Stack<KeyType>::IsFull()
{
   if(top == MaxSize -1) return 1;
   else return 0;
}

template <class KeyType>
inline int Stack<KeyType>::IsEmpty()
{
   if(top == -1) return 1;
   else return 0;
}

template <class KeyType>
void Stack<KeyType>::Add(const KeyType& x)
{
   if(IsFull()) StackFull();
   else stack[++top] = x;
}

template <class KeyType>
KeyType* Stack<KeyType>::Delete (KeyType& x)
{
   if(IsEmpty()) { StackEmpty(); return 0; }
   x = stack[top--];
   return &x;
}

template <class KeyType>
void Stack<KeyType>::StackFull()
{
   if(!suppresserrors) cout << "Danger, danger Will Robinson danger - the stack is full" << endl;
}

template <class KeyType>
void Stack<KeyType>::StackEmpty()
{
   if(!suppresserrors) cout << "Congratulations - the stack is now empty" << endl;
}
