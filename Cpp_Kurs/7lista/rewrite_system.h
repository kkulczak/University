
#ifndef REWRITE_SYSTEM_INCLUDED
#define REWRITE_SYSTEM_INCLUDED   1

#include <vector>
#include "../5lista/tree.h"

struct rewrite_system
{

   struct rule
   {
      tree left;
      tree right;

      rule( const tree& left, const tree& right ) 
         : left{ left }, right{ right } 
      { } 
   };

      
   std::vector< rule > rules;

   rewrite_system( ) { } 

   rewrite_system( const std::vector< rule > & init )
      : rules{ init }
   { }

   rewrite_system( std::vector< rule > && init )
      : rules{ std::move( init ) }
   { }
      // Inside function, rvalue-ref parameter is usual ref.

   tree one_pass( tree t ) const;
      // Make one pass through t, and try to apply a rule everywhere.
      // There are many strategies in theory, but ours is very simple.

   tree normalize( tree ) const;
      // Call one_pass, until the result doesn't change anymore. 
};

std::ostream& operator << ( std::ostream& out, const rewrite_system::rule& r );
std::ostream& operator << ( std::ostream& out, const rewrite_system& rewr );

void test();

#endif


