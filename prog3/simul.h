#ifndef SIMUL_H
#define SIMUL_H
#define Arrival        1
#define Departure      2
#define ClockStart 900
#define ClockEnd   1100
#include "list.h"
#include "queue.h"
#include <stdlib.h>


int AddTime(int Time, int Duration);        // add duratiion to a given time
int TimeDiff(int Time1,int Time2);          // compute time difference

class CentralStation{
public:
   CentralStation(int seed, int duration,int interval,int qnumber,char prn);  // constructor
   void Simulation();      // start simulation   
private:
   List<Element> EventList;
   Queue<Element> *Queues;
   int TotTime,Count,Clock,NbWickets,Seed,Duration,Interval,Icount;
   bool fullPrint;

   void Generate();                     // generate next random arrival and advance clock
                                    // Times are represented by integers on the 2400 scale.   
   void Arrive(int ArrTime,int ServTime);      // Register and process new arrival
   void Quit(int Qnumber,int DepTime); // porcess a departure
};
#endif



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





CentralStation::CentralStation(int seed, int duration,int interval,int qnumber,char prn)
{
   Seed = seed;
   srand(Seed);
   Duration = duration;
   Interval = interval;
   Icount = rand() % Interval + 1;
   if((prn == 'f') || (prn == 'F')){ fullPrint = 1; } else { fullPrint = 0; }
   NbWickets = qnumber;
   Queues = new Queue<Element>[qnumber];
   Clock = ClockStart;
   TotTime = 0;
   Count = 1;
}
 
void CentralStation::Simulation(){
   int more = 0;
   for(int i = 0;i < NbWickets;i++){ if(!Queues[i].IsEmpty()) { more = 1; } }
   while((more) || (Clock < ClockEnd))
   {
      more = 0;
      for(int i = 0;i < NbWickets;i++){ if(!Queues[i].IsEmpty()) { more = 1; } }
      Generate();
   }
   
   cout << "Ave is: " << (float)TotTime/(float)Count  << "\n";
}

void CentralStation::Generate(){

   //Arivals
   if(Clock < ClockEnd)
   {
      Icount--;
      if(Icount == 0)
      {
        Arrive(Clock, rand() % Duration +1);
        Icount = rand() % Interval + 1;
      } 
   }
   //Departurs
   Element *myE;
   for(int i = 0; i< NbWickets;i++)
   {

      if(!Queues[i].IsEmpty())  //Queues[i].QueueHead()
      {
         myE = Queues[i].QueueHead(); 
         if(myE->Duration == 0)
         {
            Quit(i,Clock);
         } else { myE->Duration--; }
      
      }
   }
   //advance the clock
   Clock++;
   if(Clock % 100 == 60) { Clock = ((Clock / 100) + 1)*100; }
   if(Clock == 2400) { Clock = 0; }
   //end clock stuff
}

void CentralStation::Arrive(int ArrTime,int ServTime){

   Element E;
   //find short Q
   int shortest = 0;
   for(int i = 0; i < NbWickets; i++)
   {
      if(Queues[i].CountQueue() < Queues[shortest].CountQueue()){ shortest = i; }
   }
   //put event in shortest queue
   E.Event = ++Count;
   E.Hour = ArrTime;
   E.Duration = ServTime;
   E.QueueNumber = shortest;
   Queues[shortest].Add(E);
   if(fullPrint) {  cout << "Event #" << E.Event << " arrived at time:  " << ArrTime << "  Event Deration:  " << ServTime << "\n"; }
}


void CentralStation::Quit(int Qnumber,int DepTime){

   Element E = *Queues[Qnumber].Delete();
   TotTime += TimeDiff(DepTime, E.Hour);
   if(fullPrint) {  cout << "Event #" << E.Event << " departed at time:  " << DepTime  << "\n"; }

}

