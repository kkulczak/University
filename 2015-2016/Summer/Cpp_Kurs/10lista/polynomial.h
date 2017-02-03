
#ifndef POLYNOMIAL_INCLUDED
#define POLYNOMIAL_INCLUDED 1

#include "varchain.h"
#include <map>

template< typename N >
struct polynomial 
{

   std::map< varchain, N, varchain::cmp > repr;

   using maptype = std::map< varchain, N, varchain::cmp > ;

   typename maptype::iterator begin( ) { return repr. begin( ); }
   typename maptype::iterator end( ) { return repr. end( ); }

   typename maptype::const_iterator cbegin( ) const { return repr. cbegin( ); }
   typename maptype::const_iterator cend( ) const { return repr. cend( ); }

   typename maptype::const_iterator begin( ) const { return cbegin( ); }
   typename maptype::const_iterator end( ) const { return cend( ); }


   const N& operator [] ( const varchain& c ) const
      { return repr[c]; }

   N& operator [] ( const varchain& c ) 
      { return repr[c]; }


   polynomial( )
      { } 
    
   polynomial( const varchain& chain ) 
   {
      repr[ chain ] = 1;
   }     

   template< typename D > 
   polynomial( const D& d )
   {
      repr[ {} ] = d; 
   }

//   polynomial(const polynomial &p) = delete;
   
   polynomial operator - ( )
   {
      auto res = *this;
      for( auto& p : res. repr )
         p. second = - p. second;
      return res;
   }
   
   polynomial& operator += ( const polynomial& pol )
   {
      for( const auto& p : pol. repr )
      {
         (*this)[ p. first ] += p. second;
      }
      return *this; 
   }

   polynomial& operator -= ( const polynomial& pol )
   {
      for( const auto& p : pol. repr )
         (*this) [ p. first ] -= p. second;
      return *this; 
   }

   template<typename X > polynomial<N> & operator *= ( X x )
   {
      for( auto& p : *this )
         p. second *= x;
      return *this; 
   }

   template< typename X > polynomial<N> & operator /= ( X x )
   {
      for( auto& p : *this )
         p. second /= x;
      return *this;
   }

};



template< typename M, typename N >
polynomial<M> operator * ( const polynomial<M> & pol, N n )
{
   auto res = pol;
   res *= n;
   return res;
}


template< typename M, typename N >
polynomial<M> operator / ( const polynomial<M> & pol, N n )
{
   auto res = pol;
   res /= n;
   return res;
}


template< typename M, typename N >
polynomial<N> operator * ( M m, const polynomial<N> & pol )
{
   auto res = pol;
   res *= m;
   return res;
}


template< typename N >
std::ostream& operator << ( std::ostream& out, const polynomial<N> & pol )
{
   bool somethingprinted = false; 

   for( auto p = pol. begin( ); p != pol. end( ); ++ p )
   {
      if( p -> second != 0 )
      {
         if( somethingprinted )
            out << " + ";
         if( p -> second != 1 )
            out << ( p -> second ) << ".";
         out << ( p -> first );

         somethingprinted = true; 
      }
   }

   if( !somethingprinted )
      out << N{0};

   return out;
}
//	Task5
template< typename N >
polynomial<N> operator + ( const polynomial<N> & p1, const polynomial<N> & p2){
	polynomial<N> result(p1);
	result += p2;
	return result;
}

template< typename N >
polynomial<N> operator - ( const polynomial<N> & p1, const polynomial<N> & p2){
	polynomial<N> result;
	result += p1;
	result += p2;
	return result;
}

template< typename N >
polynomial<N> operator * ( const polynomial<N> & p1, const polynomial<N> & p2){
	polynomial<N> result;
	for(const auto & i : p1 ){
		for(const auto & j : p2){
			result[i.first * j.first] += i.second * j.second ; 
		}
	}
	return result;
}

#endif 
















