
#include "varchain.h"
#include "polynomial.h"
#include "bigint.h"
#include "rational.h"

#if 1
template< typename N >
polynomial< N > exptaylor( unsigned int n )
{
   varchain v;

   N fact = 1;

   polynomial< N > result;
   for( unsigned int i = 0; i < n; ++ i )
   {
      result[v] += fact;
      v = v * powvar( "x" );
      fact = fact / (i+1);
   }

   return result;
}
#endif

int main(  )
{
#if 1
   std::cout << "hello\n";

   polynomial< rational > pol;

   int N = 50;

   pol[ { } ] = 1;
   pol[ { "x" } ] = rational( 1, N ); 

   
   polynomial< rational > res = 1;
 
   for( int i = 0; i < N; ++ i )
      res = res * pol;

   std::cout << "result = " << res << "\n";

   std::cout << " taylor expansion = " << exptaylor<rational>(20) << "\n";

   std::cout << "difference = " ;  
   std::cout << res - exptaylor<rational> ( 40 ) << "\n";
#endif
#if 0
	polynomial<int> a,b;
	a[{}] = 10;
	a[{"x"}] = 5;
	b[{"x"}] = 3;
	b = b*b;
	b[{"x"}] = 2;
	std::cout << a*b <<"\n";
#endif
   return 0;
}





















