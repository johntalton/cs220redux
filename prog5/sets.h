#ifndef SETS_H
#define SETS_H
#include <iostream.h>
#define MaxSetSize 200
//***************************
// set used to determan if graph cyclic
//***************************
class Sets{
   public:
      Sets(int sz = MaxSetSize){
         n = sz;
         parent = new int[sz];
         for(int i = 0; i < n; i++) parent[i] = -1;
      }
      void Union(int i, int j){ parent[i] = j; }
      int Find(int i){
         while(parent[i] >= 0) i = parent[i];
         return i;
      } 
   private:
      int *parent;
      int n;
};
#endif