#ifndef GRAPH_H
#define GRAPH_H
#include <iostream.h>
#include <fstream.h>
#include "MinMaxHeap.h"
#include "Sets.h"
#define MaxGraphSize 25

class Edge{
   public:
      int a, b, w;
      int operator>(Edge x){ return (w > x.w); };
      int operator<(Edge x){ return (w < x.w); };
      int operator>=(Edge x){ return (w >= x.w);};
      int operator<=(Edge x){ return (w <= x.w);};
      void output(ostream& os){ os << w;};
};
ostream& operator<< (ostream& os,Edge& e){
   e.output(os);
   return os;
}
//***************************
class Graph{
   public:
      Graph();
      void add(int from, int to, int weight);
      int GraphFromFile(char filename[]); // make graph from file
      MinMaxHeap<Edge> Graph::toHeap(int MinorMax);
      void Kruskal(); //Kruskals minimum cost spanig tree algorithm
      void print();
   private:
      int AdjacencyMatrix[MaxGraphSize][MaxGraphSize];
      int numEdge;
      int numVert;
};
#endif
//***************************
Graph::Graph(){
   for(int i = 0; i < MaxGraphSize; i++) 
      for(int j = 0; j < MaxGraphSize; j++) 
         AdjacencyMatrix[i][j] = -1;
}

void Graph::add(int from, int to, int weight){
   AdjacencyMatrix[from][to] = weight;
}

int Graph::GraphFromFile(char filename[]){
   ifstream mystream(filename, ios::nocreate);
   for(int i = 0; i < MaxGraphSize; i++) 
      for(int j = 0; j < MaxGraphSize; j++) 
         AdjacencyMatrix[i][j] = -1;
   if(!mystream) { cerr << "File not found\nAbort, Retry, Fail?"; return 0; }
   int from, to, weight;
   mystream >> numVert;
   mystream >> numEdge;
 
   for(i = 0; i < numEdge; i++){
      mystream >> from;
      mystream >> to;
      mystream >> weight;
      add(from,to,weight);
   }
   
   return 1;
}

void Graph::print(){
   for(int i = 0; i < MaxGraphSize; i++) {
      cout << "\n";
      for(int j = 0; j < MaxGraphSize; j++) 
         cout << AdjacencyMatrix[i][j] << " ";
   }
}

MinMaxHeap<Edge> Graph::toHeap(int MinorMax){  //add all edges into a heap
   MinMaxHeap<Edge> m(MinorMax);  
   Edge e;
   for(int i = 0; i < MaxGraphSize; i++)
      for(int j = 0; j < MaxGraphSize; j++){
         if(AdjacencyMatrix[i][j] != -1){
            e.a = i; 
            e.b = j;
            e.w = AdjacencyMatrix[i][j];
            m.Add(e);
         }
      }  
   return m;
}

void Graph::Kruskal(){
   MinMaxHeap<Edge> m(0); // 0 for min heap
   MinMaxHeap<Edge> output(0);
   Sets s;
   int count = 0;
   int aroot, broot, sum, ecount;
   sum = 0;
   ecount = 0;
   Edge x;
  
   m = toHeap(0); // 0 for min heap
   //m.p();
   while((!m.isEmpty()) && (count < (numVert-1))){
      x = *m.Del(x);
      aroot = s.Find(x.a);  //finds the root of this node
      broot = s.Find(x.b);
      if(aroot == broot){}  // if the roots of each node are 
      else{                 // the same then there is a cycle
         s.Union(aroot,broot);  // merge the two roots
         ecount++;              // count valid edges
         output.Add(x);         // add edge to final output
         sum = sum + x.w;       // total sum of edges
      }
   }
   if(ecount == (numVert - 1)){ // do we have the right number of edges
      while(!output.isEmpty()){
         x = *output.Del(x);
         cout << "Edge: " << x.a << " to " << x.b << "  - weight of " << x.w << endl;
      }
      cout << "Total weight of minimal cost spaning tree is:  " << sum << endl;
   }
   else{
      cout << "This graph has no mimimal cost spaning tree";
   }
}
 