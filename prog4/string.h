#ifndef STRING_H
#define STRING_H

class String
{
   public:
      String();
      String(char* instr, int len);
      ~String();
      String SubStr(int from, int to);
      int Length();
      int indexOf(char c);
      
      void print_String(ostream& o);
   private:
      
      char* str;
      int length;
};
#endif STRING_H

ostream& operator<< (ostream& os, String S)
{
   S.print_String(os);
   return os;
}  

String::String()
{
   length = 0;
}


String::String(char* instr ,int len)
{
   str = new char[len];
   length = len;
   str = instr;
}

String::~String(){
   delete[] str;
} 

String String::SubStr(int from, int to)
{  
   int len = to - from + 1;
   String sub("",len);

   int a = 0;
   for(int i = from-1; i < to; i++)
   {
      sub.str[a++] = str[i];
   }
   //sub[i] = 0;
   return sub;
}

int String::Length()
{
   return length;
}

int String::indexOf(char c)
{
    int index = -1;
    for(int i = 0; i < length; i++)
    {
       if(str[i] == c)
       {
          index = i;
       }
    }
    return index;
}

void String::print_String(ostream& o)
{
   o << str;
}
