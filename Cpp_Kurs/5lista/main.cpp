
#include "tree.h"
#include <iostream>

int main(  )
{

#if 1
   tree t1( std::string( "a" ));
   tree t2( std::string( "b" )); 
   tree t3 = tree( std::string( "f" ), { t1, t2 } ); 

   tree test("test", {t3,t3});
   std::cout << test << "\n";
   test = subst(test, "gwgrrggrgr", tree(""));
   std::cout << test << "\n";
   return 0;


   std::vector< tree > arguments = { t1, t2, t3 };
   std::cout << tree( "F", std::move( arguments )) << "\n";

   t2 = t3;
   t2 = std::move(t3);
 #endif
 return 0;
}



