
#include <fstream>
#include <iostream>
#include <chrono> 
#include <random>

#include "listtest.h"
#include "vectortest.h"

int main(  )
{
#if 1
   std::vector< std::string > vect( vectortest::randomstrings(10000, 50) ) ;
   std::list<std::string> l(listtest::vector_to_list(vect));
   	
   //std::cout << vect << "\n";

   auto t1 = std::chrono::high_resolution_clock::now( ); 
   listtest::sort_move( l );
   auto t2 = std::chrono::high_resolution_clock::now( );

   std::chrono::duration< double > d = ( t2 - t1 );
   //std::cout << vect << "\n";

   std::cout << "sorting took " << d. count( ) << " seconds\n";
 #endif
   return 0;
}


