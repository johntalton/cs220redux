//John Talton
//cs220 - prog 2
//4/8/98
#include <iostream.h>
#include <fstream.h>
#include "stack.h"  // Include stack lib

#define MaxSize 100

struct opLR // things to push to the stack
{           //   for post to prefix convertion
   char op;
   int LR;
};
/*/////////////////////////////////////
Expression class contains all methods
to manipulate a expretion.
     InfixtoPostfix
        converts in to postfix
     Reversve
        reverses the string
     charin
        adds a char to the end of the expretion
     fromfile
        reads the input from a file
        (future: add read next, read first,reset)
     icp & isp
        in Coming || Stack Presedence
     NexToken
        gets the next thing in expretion
        (must manualy reset current = 0)
     isOperand
        checks to see if valid char(operand)
     Validate
        is the expretion useing correct char
        (future: isPost, isPre, isIn, Null)
*//////////////////////////////////////
class Expression
{
   public:
      Expression();
      ~Expression();
      Expression InfixtoPostfix();
      Expression PosttoPrefix();
      void Reverse();
      void output(ostream& o);
      void charin(char a);
      int fromfile();
      int icp(char a);
      int isp(char a);
      char NextToken();
      int isOperand(char a);
      int Validate();
   private:
      int length;
      char exp[MaxSize];
      int current;
};

Expression::Expression() { length = 0; current = 0;}
Expression::~Expression() { }
Expression Expression::InfixtoPostfix()
{
   Expression e;
   Stack <char> stack;
   char y;
   current = 0;
   char x;

   stack.Add('#');
   for (x = NextToken(); x != '#'; x = NextToken())
   {
      if(isOperand(x)) { e.charin(x); }
      else if(x == ')')
         for (y = *stack.Delete(y); y != '(';y = *stack.Delete(y)) { e.charin(y); }
      else {
        for(y = *stack.Delete(y);isp(y) <= icp(x); y = *stack.Delete(y)) { e.charin(y);}
        stack.Add(y);
        stack.Add(x);
      }
   }

   while (!stack.IsEmpty()) {  e.charin(*stack.Delete(y));  }
   return e;
}

Expression Expression::PosttoPrefix()
{
  Expression e;
  e.length = 0;
  e.current = 0;
  current = 0;

  Stack <opLR> opstack;
  int the_counter_thingy;
  opLR temp;
  temp.op = '#';
  temp.LR = 2;
  opstack.Add(temp);

  for(the_counter_thingy = length - 2; the_counter_thingy >= 0; the_counter_thingy--)
  {
     temp = *opstack.Delete(temp); // this dec whats in the stack
     temp.LR--;
     opstack.Add(temp);

     if(isOperand(exp[the_counter_thingy])) //a thing lick a b c or somehting
     {
        e.charin(exp[the_counter_thingy]);
     }
     else
     {
        temp.op = exp[the_counter_thingy];
        temp.LR = 2;
        opstack.Add(temp);
     }


     temp = *opstack.Delete(temp);
     if(temp.LR == 0)
     {  // add loop here while not # or not 0
        while(temp.LR == 0)  // if code error this could
        {                    // cause problems
           e.charin(temp.op);
           temp = *opstack.Delete(temp);
        }
        opstack.Add(temp);
     }
     else
     {
        opstack.Add(temp);
     }

  }
  e.Reverse();
  return e;
}

void Expression::Reverse()
{
   char temp[MaxSize];
   int countdown;
   int countup = 0;

   for(countdown = length ; countdown >= 0; countdown--)
   {
      temp[countup++] = exp[countdown];
   }
   temp[countup] = '#';
   length = countup;

   for(int x = 0; x <= length; x++)  { exp[x] = temp[x]; }
}

void Expression::output(ostream& o)
{
   int i;
   for(i = 0; i < length; i++)
   {
      if(exp[i] != '#') o << exp[i];
   }
}

void Expression::charin(char a)
{
   exp[length] = a;
   length++;
   exp[length] = '#'; // add # just to make shure

}

int Expression::fromfile()
{
   char ch;
   length = 0;

   static ifstream mystream("express.dat", ios::nocreate);
   if(!mystream) { cerr << "File not found\nAbort, Retry, Fail?"; return 0; }
   mystream >> ch;
   if (ch == '#') { mystream.close(); return 0; }
   while(ch != '#')
   {
      exp[length] = ch;
      length++;
      mystream >> ch;
   }
   exp[length] = '#';
   return 1;
}

int Expression::icp(char a)
{
   int blah;
   switch (a)
   {
      case '+': blah = 3; break;
      case '-': blah = 3; break;
      case '*': blah = 2; break;
      case '/': blah = 2; break;
      case '(': blah = 0; break;
   }
   return blah;
}

int Expression::isp(char a)
{
   int this_is_a_temp_var;
   switch (a)
   {
      case '#': this_is_a_temp_var = 5; break;
      case '+': this_is_a_temp_var = 3; break;
      case '-': this_is_a_temp_var = 3; break;
      case '*': this_is_a_temp_var = 2; break;
      case '/': this_is_a_temp_var = 2; break;
      case '(': this_is_a_temp_var = 4; break;
   }
   return this_is_a_temp_var;
}

char Expression::NextToken()
{
   char a;
   if(current > length) return '#'; //we are at or past the end
   a = exp[current];
   current++;
   return a;
}

int Expression::isOperand(char a)
{
   if((a =='+') || (a =='-') || (a =='/') || (a =='*') || (a == '(') || (a == ')')) return 0;
   return 1;
}

int Expression::Validate()
{
   char checkchar;
   int i;
   if(!length && exp[length] != '#') return 0;
   for(i = 0; i <= length; i++)
   {
      checkchar = exp[i];
      if(((checkchar <= 'z') && (checkchar >= 'a')) ||
         ((checkchar <= 'Z') && (checkchar >= 'A')) ||
         (!isOperand(checkchar)) ||
         (checkchar == '#')) {}
      else
         return 0;
   }
   // add in to check make shur this is truly a infix equassion
   //    return if it is a infix postfix or prefix equassion
   return 1;
}

//
//overload the ouput for Expression class
//
ostream& operator<< (ostream& os,Expression& e)
{
   e.output(os);
   return os;
}


//Main
void main()
{
   Expression ex;
   Expression postex;

   cout << "Infix           Postfix          Prefix" << endl;
   while(ex.fromfile())
   {
      if(!ex.Validate()) { cout << "Ill formed expression - Use (A-Z, a-z, +-/*)\n"; }
      else
      {
         postex = ex.InfixtoPostfix();
         cout << ex << "   =>    " << postex << "   =>    " << postex.PosttoPrefix() << endl;
      }
   }
}
//EOF
