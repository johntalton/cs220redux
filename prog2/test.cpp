#include "stack.h"
#include <iostream.h>
void main()
{
   Stack <char> Mystack;
   char y;
   Mystack.Add('a');
   Mystack.Add('b');
   Mystack.Add('c');      
   while (!Mystack.IsEmpty()) cout << *Mystack.Delete(y);
}