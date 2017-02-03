
#ifndef FIFTEEN_INCLUDED
#define FIFTEEN_INCLUDED  1

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <list>

#include "move.h"


class fifteen
{
private: 
   static constexpr size_t dimension = 4;
      // Test for different dimensions. Don't be lazy!

   static_assert( dimension > 1, "dimension must be two at least" );

   using position = std::pair< size_t, size_t > ;

public:
   size_t table [ dimension ][ dimension ];
      // We use the numbers 1 .. dimension*dimension-1 for the tiles,
      // and 0 for the open place.

   size_t open_i;
   size_t open_j;
      // Position of the open place. Use matrix notation, i is row, 
      // j is column. 

   
   static size_t distance( size_t i1, size_t i2 )
      { return i1 > i2 ? i1 - i2 : i2 - i1; }
         // Distance between two numbers.

   static size_t distance( position p1, position p2 )
      { return distance( p1. first,  p2. first ) +
               distance( p1. second, p2. second ); }
         // Manhattan distance between positions p1 and p2.

   static position solvedposition( size_t val ){
   	if (val == 0)	return position ( dimension-1, dimension-1 );
   	return  position( (val-1) / dimension, (val-1) % dimension );
   }
      // Position where val must be in the solution.  

public:
   fifteen( )
   :	open_i{dimension-1},
   	open_j{dimension-1}
   {
   	int val = 1;
   	for(size_t i=0; i < dimension; i++){
   		for(size_t j=0; j < dimension; j++, val++){
   			table[i][j] = val;
   		}
   	}
   	table[dimension-1][dimension-1] = 0;
   }


   fifteen( std::initializer_list< std::initializer_list< size_t >> init )
   {	size_t row=0;
   	for ( auto i = init.begin() ; i != init.end(); i++, row++){
   		size_t col=0;
   		for( auto j = (*i).begin() ; j != (*i).end(); j++, col++){
   			if(*j == 0){
   			open_i = row;
   			open_j = col;
   			} 
   			table[row][col] = *j;
   		}
   	}
   }

   void makemove( move m ){
   	switch(m){
   	case move::up :
   		if(open_i == 0)	throw illegalmove(m);
   		std::swap(table[open_i][open_j], table[open_i-1][open_j] );
   		open_i--;
   		break;
   	case move::down :
   		if(open_i == dimension-1)	throw illegalmove(m);
   		std::swap(table[open_i][open_j], table[open_i+1][open_j] );
   		open_i++;
   		break;
   	case move::left :
   		if(open_j == 0 )	throw illegalmove(m);
   		std::swap(table[open_i][open_j], table[open_i][open_j-1] );
   		open_j--;
   		break;
   	case move::right :
   		if(open_j == dimension -1)	throw illegalmove(m);
   		std::swap(table[open_i][open_j], table[open_i][open_j+1] );
   		open_j++;
   		break; 
   	}
   }
      // This method tries to make a move m. If it fails then 
      // it throws illegalmove( move ); 
      // Note that in C++, you don't have to declare possible exceptions.
      // A move is illegal if it would move the open place out of the
      // board. 

   void makemove( const std::list< move > & moves ) 
   {
      for( move m : moves ) makemove(m);
   }

      
   size_t distance( ) const{
   	size_t ret=0;
   	for(size_t i=0; i < dimension; i++){
   		for(size_t j=0; j < dimension; j++){
   			position p = solvedposition(table[i][j]);
   			ret += distance(p, position(i,j));
   		}
   	}
   	return ret;
   }
      // Estimated distance from solution. Use Manhattan distance,
      // see the wikipedia article. 

   bool issolved( ) const{
#if 0
   	for(size_t i=0; i<dimension; i++){
   		for(size_t j=0; j<dimension; j++){
   			if( i == dimension - 1 && j == dimension -1 && table[i][j] ==0 )	return true;
   			if( table[i][j] != i*dimension + j + 1 )	return false;
   		}
   	}
   	return true;
#endif
	return distance() == 0;
  
   }
      // True if the puzzle is in solved state.

   size_t hashvalue( ) const{
   	size_t hash=0;
   	for(size_t i=0; i < dimension * dimension; i++)	
   		hash = hash * dimension * dimension * 2 + table[i/dimension][i%dimension];
   	return hash;
   }
   
      // Construct a hash value on the state.

   bool equals( const fifteen& other ) const{
   	for(size_t i=0; i<dimension; i++){
   		for(size_t j=0; j<dimension; j++){
   			if( table[i][j] != other.table[i][j] )	return false;
   		}
   	}
   	return true;
   }
     

   friend std::ostream& operator << ( std::ostream& , const fifteen& f ); 
};

std::ostream& operator << ( std::ostream& stream, const fifteen& f );

#endif

