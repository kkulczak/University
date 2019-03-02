
// Written by Hans de Nivelle, July 2011.

#ifndef BIGINT_INCLUDED
#define BIGINT_INCLUDED   1

#include <iostream> 
#include <vector> 
#include <stdexcept>

class bigint
{
public: 
   typedef unsigned short int word;

private:
   std::vector< word > repr;
      // Least significant words come first.

   int sign;
      // 1 denotes positive, -1 denotes negative. 

public: 
   // Compare two blocks of words of equal length. The iterators
   // p1, p2 must be set at the end of the blocks. 
   // (One position behind it.) 

   static int compare( std::vector< word > :: const_iterator p1,
                       std::vector< word > :: const_iterator p2,
                       unsigned int len );

   static int compare( const std::vector< word > & v1,
                       const std::vector< word > & v2 );
      // Is only correct when there are no non-significant
      // zeroes. 

   static int compare( const bigint& i1, const bigint& i2 ); 


   // The following method is part of the multiplication algorithm.
   // It adds ( q1 .. q2 ) * factor to ( p1 .. ).
   // The result has to fit.

   static void add( std::vector< word > :: iterator p1,
                    std::vector< word > :: const_iterator q1,
                    std::vector< word > :: const_iterator q2,
                    word factor );

   // The following method is part of the division algorithm.
   // We try to subtract ( q1 .. q2 ) * factor from ( p1 .. p2 );restword.
   // p2 is computed from the length q2 - q1. After the subtraction,
   // restword must be zero. 
   // It is possible that the subtraction does not fit, because
   // the estimated factor can be one too high. (More should not
   // happen, but some bad estimation algorithms produce 2 too high.) 
   // In that case, the factor is decreased by one until the subtraction
   // fits. We return the highest factor that fits. 
   // If the original estimation was good, this is the original
   // factor or 1 less.

   static word subtract( std::vector< word > :: iterator p1,
                         word restword, 
                         std::vector< word > :: const_iterator q1,
                         std::vector< word > :: const_iterator q2,
                         word factor );

   static void add( std::vector< word > :: const_iterator p1,
                    std::vector< word > :: const_iterator p2, 
                    std::vector< word > :: const_iterator q1,
                    std::vector< word > :: const_iterator q2,
                    std::vector< word > :: iterator r1,
                    std::vector< word > :: iterator r2 );
      // r1 .. r2 should be large enough to hold the result.
      // Otherwise, it will be very very bad.
      // It is guaranteed that all words in r1 .. r2 are written. 

   static void subtract( std::vector< word > :: const_iterator p1,
                         std::vector< word > :: const_iterator p2,
                         std::vector< word > :: const_iterator q1,
                         std::vector< word > :: const_iterator q2,
                         std::vector< word > :: iterator r1,
                         std::vector< word > :: iterator r2 );
      // r1 .. r2 should be large enough to hold the result, and
      // the result must be positive. It is guaranteed that all words
      // in the range r1 .. r2 are written.

   static void addorsub( const bigint& b1, const bigint& b2, int s2,
                         bigint& r ); 
      // It is possible that b1 is the same as r, or b2 is the same
      // as r. Dependent on the sign of b2 and s2, we add or subtract,
      // and put the result in res. 

   static void multiply( const std::vector< word > & v1,
                         const std::vector< word > & v2,
                         std::vector< word > & res );
      // This function will not work correctly when res is identical
      // to v1 or v2. res should be zero in advance, and it
      // should be big enough to contain the result, because
      // multiply does not check this. 


   // Divide (x1,x2,x3) / (y1,y2). This is used as estimation for the
   // real big division. x1 and y1 are the most significant word.
   // The result (x1,x2,x3)/(y1,y2) can be 0X10000, due to the fact that 
   // the estimated result can be too high. 

   // We tried different implementations, but it turned out that 
   // the simplest one, based on floating point, is the most
   // efficient.

   static unsigned int divide_fp( word x1, word x2, word x3,
                                  word y1, word y2 )
   {
      return static_cast< unsigned int > (
             ( x1 * 65536.0 * 65536.0 + x2 * 65536.0 + x3 ) /
             ( y1 * 65536.0 + y2 ));
   }


   static unsigned int divide( word x1, word x2, word x3,
                               word y1, word y2 );

   static std::vector< bigint::word >
          divide( const std::vector< word > & d, 
                  std::vector< word > & rest );
      // The most significant bit in d must not be zero.
      // Subtract d from rest as many times as possible.
      // How many times will be returned. 

   // Ensure that our vector has length at least s:

   void ensure( unsigned int s )
   {
      while( repr. size( ) < s )
         repr. push_back(0);
   }

   // Remove leading, non-significant zeroes:

   void reduce( )
   {
      while( repr. size( ) && repr. back( ) == 0 )
         repr. pop_back( );
   }

   bigint( const std::vector< word > & v, int s )
      : repr(v),
        sign(s)
   { }

public: 
   bigint( ) 
      : sign( 1 )
   { }


   bigint( unsigned int x );
   bigint( int x );

   // We test that a word is 16 bits and unsigned.
   // We test that an unsigned int is 32 bits and unsigned. 
   // We check that right shifts have no sign extension.

   static bool testmachine( ); 

   // Checksum can be used for checking operations.

   unsigned int checksum( unsigned int prime ) const;

   void operator += ( const bigint& b ) { addorsub( *this, b, 1, *this ); } 
   void operator -= ( const bigint& b ) { addorsub( *this, b, -1, *this ); }
   bigint operator + ( const bigint& b ) const
                                         { bigint res;
                                           addorsub( *this, b, 1, res );
                                           return res; }
   bigint operator - ( const bigint& b ) const  
                                         { bigint res;
                                           addorsub( *this, b, -1, res );
                                           return res; }

   bigint operator * ( const bigint& b ) const 
   {
      bigint res;
      res. ensure( repr. size( ) + b. repr. size( ));
      multiply( repr, b. repr, res. repr );
      res. reduce( );
      res. sign = sign * b. sign; 
      return res; 
   }

   void operator *= ( const bigint& b )
   {
      bigint res;
      res. ensure( repr. size( ) + b. repr. size( ));
      multiply( repr, b. repr, res. repr );
      res. reduce( );
      sign *= b. sign; 
      res. repr. swap( this -> repr );
   }

   bigint operator / ( const bigint& b ) const 
   {
      if( b. repr. size( ) == 0 )
         throw std::runtime_error( "cannot divide by zero" ); 

      bigint i = *this;
      bigint quot = bigint( divide( b. repr, i. repr ), sign * b. sign ); 
      quot. reduce( );
      return quot;
   } 

   void operator /= ( const bigint& b )
   {
      if( b. repr. size( ) == 0 )
         throw std::runtime_error( "cannot divide by zero" ); 

      bigint i = * this; 
      *this = bigint( divide( b. repr, i. repr ), sign * b. sign );
      reduce( ); 
   }

   bigint operator % ( const bigint& b ) const 
   {
      if( b. repr. size( ) == 0 )
         throw std::runtime_error( "cannot divide by zero" );

      bigint i = *this; 
      divide( b. repr, i. repr );
      i. reduce( );
      return bigint( i. repr, sign ); 
   }

   bigint operator - ( ) const
   {
      return bigint( repr, - sign );
   }

   int getsign( ) const
   {
      return sign;
   }

   unsigned int getunsigned( ) const
   {
      if( repr. size( ) >= 2 )
         throw std::runtime_error( "cannot make unsigned, number is too big" );

      if( repr. size( ) == 0 )
         return 0;
      else
         return repr. front( );
   }

   static bigint gcd( bigint i1, bigint i2 ); 
   
   double approximation( ) const;
     
   static bigint factorial( unsigned int k );
 
   friend std::ostream& operator << ( std::ostream& stream, bigint b );
   
};



inline bool operator == ( const bigint& i1, const bigint& i2 )
{
   return bigint::compare(i1,i2) == 0;
}

inline bool operator != ( const bigint& i1, const bigint& i2 )
{
   return bigint::compare(i1,i2) != 0;
}

inline bool operator < ( const bigint& i1, const bigint& i2 )
{
   return bigint::compare(i1,i2) == -1;
}

inline bool operator > ( const bigint& i1, const bigint& i2 )
{
   return bigint::compare(i1,i2) == 1;
}

inline bool operator <= ( const bigint& i1, const bigint& i2 )
{
   return bigint::compare(i1,i2) != 1;
}

inline bool operator >= ( const bigint& i1, const bigint& i2 )
{
   return bigint::compare(i1,i2) != -1;
}


#endif

