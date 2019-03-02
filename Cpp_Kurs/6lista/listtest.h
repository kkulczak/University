
#ifndef LISTTEST_INCLUDED
#define LISTTEST_INCLUDED   1

#include <list> 
#include <string> 
#include <fstream>
#include <iostream>
#include <vector>

// I agree that the use of namespace in this little exercise
// is a bit exagerated, but one has to learn this technique.

namespace listtest 
{

   std::list<std::string> readfile( std::istream& input );


   std::list<std::string> randomstrings( size_t nr, size_t s );
      // Return nr random strings of length s.
 
   void sort_assign( std::list< std::string > & v );
      // Sort the list with bubble sort, using assignments for the exchanges.

   void sort_move( std::list< std::string > & v );
      // Sort the list with bubble sort, using std::swap for the exchanges.

   void sort_std( std::list< std::string > & v );
      // Sort using std::sort.
   std::list<std::string> vector_to_list(const std::vector<std::string> &v);

}

std::ostream& 
operator << ( std::ostream& out, const std::list< std::string > & l);
   // Must be not in namespace. 

#endif 


