#include <iostream.h>
#include "simul.h"
//#include "simul.cpp"

void main()
{
   
   int a,b,c,d;
   char e;
   

   while(1)
   {
      cout << "\nEnter Nuber of Queues(0 to end):  ";
      cin >> d;
      if(!d) { break; }
      cout << "Enter a random seed:  ";
      cin >> a;
      cout << "\nEnter Max Duration(2-9):  ";
      cin >> b;
      cout << "\nEnter Max Interval(2-9):  ";
      cin >> c;
      cout << "\nEnter \"f\" If you want full print out:  ";
      cin >> e;
      cout << "\n\n";
      CentralStation mystation(a, b, c, d,e);
      mystation.Simulation();
   }
   cout << "End Microsuck Sim98";
	
}