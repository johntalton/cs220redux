#include <iostream.h>
#include <stdlib.h>
#include "simul.h"
enum bool {false, true};


int AddTime(int Time, int Duration){// add duratiion to a given time
   int Hours,Minutes;
   Hours = Time / 100;
   Minutes = Time % 100 + Duration;
   if(Minutes>59){ Minutes -= 60; Hours++; }
   return Hours *100 + Minutes;
}

int TimeDiff(int Time1,int Time2){// compute time difference
   int Min1,Min2,Hour1,Hour2,DiffMin;
   if(Time1>Time2){ // compute difference
      Hour1 = Time1 / 100;   Min1 = Time1 % 100;
      Hour2 = Time2 / 100;   Min2 = Time2 % 100;
      if(Min1>Min2) // straight defference
         DiffMin = Min1 - Min2;
      else{
         DiffMin = Min1 + 60 - Min2; Hour1--;
      }
      return (Hour1-Hour2)*100+DiffMin;
   }else return 0;
}



