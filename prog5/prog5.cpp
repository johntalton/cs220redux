#include "Graph.h"
#include <iostream.h>
/****************************
* John Talton
* This program is a example of graphs
*  and the use of kruskal's algorithum
*  to determan a minimal cost spanig tree
*
* It read graphs from a file specifyed by
*  the user. the file must be in the fromat
*  of:
*     NumVert NumEdge [Vert Vert Weight]
****************************/
void main(){
   Graph g;
   char filename[13];

   cout << "Enter a file to read from:  ";
   cin.get(filename, 12, '\n');
   cin.ignore(80,'\n');
   cout << endl;
   while(filename[0] != '\0'){
      if(g.GraphFromFile(filename)){
           //g.print();
           g.Kruskal();
      }
      cout << "\n\nEnter a file to read from:  " << flush;
      cin.get(filename, 12, '\n');
      cin.ignore(80,'\n');
      cout << endl << flush;
   }
   cout << "End of Kruskal's Algorithm by ¥NöP\n";
}
