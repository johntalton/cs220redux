/*
John Talton
prog4
5/5/98
This Prog takes in sets of two string read from a file
spesified by the user.  Then using the two strings it
calculates and forms a bianary Tree.  Then lastlay it
prints out the Pre Post and InOrder traversals.
*/
#include <iostream.h>
#include <fstream.h>
#include <string.h>
#include "btree.h"
#define  MaxSize 27


//This is your fromfile function. it reads from a file spesified
// by the user and returns a IO and PO string.  it also returns
// true if not the end of file and false if end of file
int fromfile(char filename[], char IO[MaxSize], char PO[MaxSize])
{
   char ch = ' ';

   static ifstream mystream(filename, ios::nocreate);
      if(!mystream) { cerr << "File not found\nAbort, Retry, Fail?"; return 0; }

   int i=0;
   while(ch != '#') {
      mystream >> ch;
      IO[i++] = ch;
   }
   if(IO[0] == '#') { mystream.close(); return 0; }
   IO[i - 1] = '\0';
   ch = ' ';
   i=0;
   while(ch != '#') {
      mystream >> ch;
      PO[i++] = ch;
   }
   PO[i - 1] = '\0';
   return 1;
}

void main(){
   char filename[13];
   char InOrder[MaxSize];
   char PostOrder[MaxSize];
   BTree<char> B;

   cout << "Enter a file to read from:  ";

   cin.getline(filename, 12, '\n');
   cout << endl;
   while(fromfile(filename, InOrder, PostOrder))
   {
      B.MakeTree(InOrder, PostOrder);

      cout << "Tree Traversals: \n" << "InOrder:   ";
      B.InOrder();
      cout << "\nPostOrder: ";
      B.PostOrder();
      cout << "\nPreOrder:  ";
      B.PreOrder();
      cout << "\n" << endl;
      cout << B << "\n\n";
   }
   cout << "End of MakeTree by ¥NöP\n";
}
