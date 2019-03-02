
#include "vectortest.h"

#include <random>
#include <chrono> 
#include <algorithm>
#include <ctype.h>

std::vector< std::string >
vectortest::randomstrings( size_t nr, size_t s )
{
   static std::default_random_engine gen( 
      std::chrono::system_clock::now( ). time_since_epoch( ). count( ) );
         // Narrowing long int into int, but that is no problem.

   static std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ012345689";
   static std::uniform_int_distribution<int> distr( 0, alphabet. size( ) - 1);
      // More narrowing.

   std::vector< std::string > res;

   for( size_t i = 0; i < nr; ++ i )
   {
      std::string rand;
      for( size_t j = 0; j < s; ++ j )
      {
         rand. push_back( alphabet[ distr( gen ) ] );  
      }

      res. push_back( std::move( rand ));
   }
   return res;
}
         


std::vector<std::string> vectortest::readfile( std::istream& input ) {
	std::vector<std::string> v;
	char c;
	std::string s;
	while(input.good()){
		input >> c;
			if( isspace(c) || ispunct(c) ){
				v.push_back(std::move(s));
				s.clear();
			}
			else{
				s.push_back(c);
			} 
	}
	return v;
}
#if 1
void vectortest::sort_assign( std::vector< std::string > & v ){
	for(size_t j=0; j < v.size(); j++){
		for(size_t i=0; i<j; i++){
			if( v[i] > v[j] ){
				std::string s= std::move(v[i]);
				v[i] = std::move(v[j]);
				v[j] = std::move(s);
			}
		}
	}
}

void vectortest::sort_move( std::vector< std::string > & v ){
	for(size_t j= 0; j < v.size(); j++){
		for(size_t i= 0; i < j; i++){
			if( v[i] > v[j] ){
				std::swap( v[i], v[j]);
			}
		}
	}
}

void vectortest::sort_std( std::vector< std::string > & v ){
	std::sort( v.begin(), v.end() );
}
#endif

std::ostream& operator << ( std::ostream& out, const std::vector< std::string > & vect ){
	for(const std::string& i : vect){
		out << i <<", ";
	}
	out << '\n';
	return out;
}




