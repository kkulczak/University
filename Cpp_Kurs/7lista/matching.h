

#ifndef MATCHING_INCLUDED
#define MATCHING_INCLUDED  1

#include <map>
#include <list>

#include "../5lista/tree.h"

struct matching
{
   std::map< std::string, tree > subst;


   matching( ) { }

   matching( std::initializer_list< std::pair< std::string, tree >> init )
   { 
      for( const auto& assign : init )
         subst. insert( { assign. first, assign. second } );
   }

   bool isdefined( const std::string& s ) const
      { return subst. find(s) != subst. end( ); }
         // True if variable s is in our domain. 
   
   // True if we consider the string a variable.
   // This is the case when it starts with an underscore.

   static bool isvariable( const std::string& s )
   {
      return s. size( ) >= 2 && s[0] == '_';
   }


   // Exercise : Remove the const here, try to substitute something.
   // Observe what you see.
 
   tree operator( ) ( const std::string& s ) const 
   {
      return subst. at(s); 
   }

   tree operator( ) ( const tree& t ) const;
      // Similar to the substitution function that you made already
      // in task 5. 
      // Throws an exception if there is an unknown variable.
    
   bool assign( const std::string& s, const tree& val )
   {
      return subst. insert( { s, val } ). second;
   }

};

std::list< matching > match( tree from, tree into );
   // Try to match (from) into (into). Return a one-element list,
   // on success, and empty list on failure.

std::ostream& operator << ( std::ostream& out, const matching& m );


#endif



