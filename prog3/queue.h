
#ifndef QUEUE_H
#define QUEUE_H
#define DefaultSize 100

class Element{
public:
   int Event;
   int Hour;
   int Start;
   int Duration;
   int QueueNumber;
   int operator<(const Element& e){
      return Hour<e.Hour;
   }
};

template <class KeyType>
class Queue{
private:
   int front,rear;
   KeyType *queue;
   int MaxSize;
public:
   Queue(int MaxQueueSize=DefaultSize){ // create an empty queue whose size is MaxqueueSize
      MaxSize = MaxQueueSize;
      queue = new KeyType[MaxSize];
      front = rear = -1;
   }
   bool IsFull(){ // if number of elemnets in the queue is equal to the maximum size, return true
               // else return false   
      if(rear==MaxSize-1) return true;
      else return false;
   }
   void Add(const KeyType& item){ // insert item at rear of the queue
      if(IsFull()) 
         cout<<"No enough space in the queue";
      else queue[++rear] = item;
   }
   bool IsEmpty(){ // if number of elements is 0, return true, else return false
      if(front==rear) return true;
      else return false;
   }
   KeyType *Delete(){ // remove the item at the front of the queue
      if(IsEmpty()){ cout<<"Delete in an empty queue"; return 0; }
      return queue+(++front);
   }
   KeyType *QueueHead(){
      if(IsEmpty()){ cout<<"Delete in an empty queue"; return 0; }
      return queue+front+1;
   }
   int CountQueue(){
      return rear-front;
   }
};
#endif
