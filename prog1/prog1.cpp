// John Talton
// CS220 Prog1.cpp
// 439-57-4799
#include <iostream.h>
#include <fstream.h>
#include <math.h>
/*****************************************************/
#if defined(__MSDOS__)
#endif
#if defined(_WIN32)
#endif
#if !defined(__MSDOS__) && !defined(_WIN32)
   #error Can not compile - Incorect platform
#endif
/*****************************************************/
#define MaxTerms 100
class Polynomial;
char compare(int a,int b);
ostream& operator<<(ostream& os,Polynomial& p);
/////////////////////////////////////////////////
/* Class Term:
      this class holds a term (coef)x^(exp)
///////////////////////////////////////////////*/
class term
{
   friend Polynomial;
   private:
      float coef;
	 int exp;
};
/////////////////////////////////////////////////
/* Class Polynomial:
    this class is the constructor and
    destructor. also it contains all member
    function for mimipulation of polynomials

    public:
       Polynomial();
          constructor
       ~Polynomial();
          destructor
       void polyout(ostream& o);
          print out the polynomial
       int operator!();
          if exits return 1 else 0
       float Coef(int e);
          returns the coef of x^e
       int LeadExp();
          returns the larges exponent
       Polynomial Add(Polynomial poly);
          adds a polynomial (poly) to this
       Polynomial Mult(Polynomial poly);
          multiplys polynomial (poly) to this
       float Eval(float f);
          evaluats this at f
       int PolyFromfile();
          reads a polynomial for a file
       void NewTerm(float c,int e);
          creats new terms in the polynomial
    private:
       Polynomial TermMult(term t);
          multiplys this with a term (t)
       term termArray[MaxTerms];
          holds the actuall polynomial
       int Terms;
          number of terms in the polynomial
///////////////////////////////////////////////*/
class Polynomial
{
   public:
      Polynomial();
      ~Polynomial();
      void polyout(ostream& o);
	   int operator!();
	   float Coef(int e);
	   int LeadExp();
	   Polynomial Add(Polynomial poly);
	   Polynomial Mult(Polynomial poly);
	   float Eval(float f);
	   int PolyFromfile();
	   void NewTerm(float c,int e);
   private:
	   Polynomial TermMult(term t);
	   term termArray[MaxTerms];
	   int Terms;
};
Polynomial::Polynomial()  { Terms = 0;}
Polynomial::~Polynomial()  { }
void Polynomial::polyout(ostream& o)
{
   int a = 0;
   if(Terms == 0) { o << '0'; return; }
   while(a < Terms)
   {
      if((termArray[a].coef == 1) && (termArray[a].exp != 0)) {} else { o << termArray[a].coef; }
      if(termArray[a].exp  == 0) {}
      else {
         if(termArray[a].coef == 0) {}
         else
         {
            o << 'x';
            if(termArray[a].exp == 1) {}
            else
            {
               o << '^';
               o << termArray[a].exp;
            }
         }
      }
      if (a < Terms - 1) o << " + ";
      a++;
   }
}
int Polynomial::operator!()
{
   int flag = 1;
   for(int i = 0; i < Terms; i++)
      if(termArray[i].coef != 0)
         flag = 0;
   return flag;
}
float Polynomial::Coef(int e)
{
   int a = 0;
   while ((e != termArray[a].exp) && (a < Terms))
   {
      a++;
   }
   if(a == Terms) { return 0; }
   return termArray[a].coef;
}
int Polynomial::LeadExp()
{
   return termArray[0].exp;
}
Polynomial Polynomial::Add(Polynomial poly)
{
   Polynomial C;
   int a = 0;
   int b = 0;
   float x;
   int termcount = 0;

   while ((a < Terms) && (b < poly.Terms))
   {
      switch (compare(termArray[a].exp, poly.termArray[b].exp))
      {
          case '=':
	          x = termArray[a].coef + poly.termArray[b].coef;
             if (x)
             {
                C.NewTerm(x,termArray[a].exp);
                termcount++;
             }
             a++; b++;
             break;
          case '<':
             C.NewTerm(poly.termArray[b].coef,poly.termArray[b].exp);
             b++;
             termcount++;
             break;
          case '>':
             C.NewTerm(termArray[a].coef, termArray[a].exp);
             a++;
             termcount++;
             break;
      }
   }
   for(;a < Terms; a++)
   {
      C.NewTerm(termArray[a].coef, termArray[a].exp);
      termcount++;
   }
   for(;b < poly.Terms; b++)
   {
      C.NewTerm(poly.termArray[b].coef, poly.termArray[b].exp);
      termcount++;
   }
   C.Terms = termcount;
   return C;
}
Polynomial Polynomial::Mult(Polynomial poly)
{
   int i = 0;
   Polynomial sum;
   while(i < poly.Terms)
   {
      //if((poly.termArray[i].coef == 0)) {}
      if(!poly) {}
      else
      {
         sum = sum.Add(TermMult(poly.termArray[i]));
      }
      i++;
   }
   return sum;
}
float Polynomial::Eval(float f)
{
   float sum = 0;
   for(int i = 0; i < Terms; i++)
   {
        sum += (float)((pow(f,termArray[i].exp)) * termArray[i].coef);
   }
   return sum;
}
int Polynomial::PolyFromfile()
{
   int num;
   int m;
   float n;
   static ifstream mystream("multiply.dat", ios::nocreate);
   if(!mystream) { cerr << "File not found\nAbort, Retry, Fail?"; return 0; }
   mystream >> num;
   if (!num) { mystream.close(); return 0; }
   Terms = num;
   for(int i = 0; i < num; i++)
   {
      mystream >> n;
      mystream >> m;
      termArray[i].coef = n;
      termArray[i].exp  = m;
   }
   return 1;
}
void Polynomial::NewTerm(float c,int e)
{
   if(Terms != MaxTerms)
   {
      termArray[Terms].coef = c;
      termArray[Terms].exp  = e;
      Terms++;
   }
   else
   {
      cout << "An overflow error has occured at " << this << ": Too many terms:  "; return; }
}
Polynomial Polynomial::TermMult(term t)
{
   Polynomial p;
   int a;
   for(a = 0; a <= Terms; a++)
   {
      p.NewTerm(termArray[a].coef * t.coef,termArray[a].exp + t.exp);
   }
   p.Terms = Terms;
   return p;
}
char compare(int a,int b)
{
   if (a == b) return '=';
   else if (a > b) return '>';
   else return '<';
}
/////////////////////////////////////////////////
/* overloads the output and prints the polynomial
///////////////////////////////////////////////*/
ostream& operator<< (ostream& os,Polynomial& p)
{
   p.polyout(os);
   return os;
}
/////////////////////////////////////////////////
/* MAIN
///////////////////////////////////////////////*/
void main()
{
   Polynomial X;
   Polynomial Y;
   while(X.PolyFromfile() && Y.PolyFromfile())
   {
      cout << '(' << X << ")  *  (" << Y << ")  =  " <<  X.Mult(Y) << endl;
   }
}