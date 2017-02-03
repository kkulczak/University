
#ifndef RATIONAL_INCLUDED
#define RATIONAL_INCLUDED   1


#include "bigint.h"


struct rational
{
   bigint num;
   bigint denum;


   void normalize( )
   {
      bigint g = bigint::gcd( num, denum );
      num /= g;
      denum /= g;

      if( denum < 0 )
      {
         num = - num;
         denum = - denum;
      }

      if( num == 0 )
         denum = 1;
   }

   rational( ) 
      : num( 0 ), denum( 1 )
   { }

   rational( const bigint& num, const bigint& denum )
      : num( num ), denum( denum )
   {
      normalize( );
   }

   rational( unsigned int num, unsigned int denum )
      : num( num ), denum( denum )
   {
      normalize( );
   }

   rational( int num, int denum )
      : num( num ), denum( denum )
   {
      normalize( );
   }

   rational( unsigned int num )
      : num( num ), denum(1)
   { }

   rational( int num )
      : num( num ), denum(1)
   { }
 
   rational( const bigint& num )
      : num( num ), denum(1)
   { }

   void operator *= ( const rational& r )
   {
      num *= r. num;
      denum *= r. denum;
      normalize( );
   }

   void operator /= ( const rational& r )
   {
      num *= r. denum;
      denum *= r. num;
      normalize( );
   }

   double approximation( ) const
   {
      return num. approximation( ) / denum. approximation( );
   }

};


inline rational operator + ( const rational& r1, const rational& r2 )
{
   rational res = rational( r1. num * r2. denum + r2. num * r1. denum,
                            r1. denum * r2. denum );
   return res;
}

inline rational operator - ( const rational& r1, const rational& r2 )
{
   rational res = rational( r1. num * r2. denum - r2. num * r1. denum,
                            r1. denum * r2. denum );
   return res;
}

inline void operator += ( rational& r1, const rational& r2 )
{
   r1 = r1 + r2; 
}

inline void operator -= ( rational& r1, const rational& r2 )
{
   r1 = r1 - r2; 
}

inline rational operator * ( const rational& r1, const rational& r2 )
{
   rational res = rational( r1. num * r2. num, r1. denum * r2. denum );
   return res;
}

inline rational operator / ( const rational& r1, const rational& r2 )
{
   rational res = rational( r1. num * r2. denum, r1. denum * r2. num );
   return res;
}

inline rational operator - ( const rational& r )
{
   return rational( - r. num, r. denum );
}


inline bool operator == ( const rational& r1, const rational& r2 )
{
   return r1. num * r2. denum == r1. denum * r2. num;
}

inline bool operator != ( const rational& r1, const rational& r2 )
{
   return r1. num * r2. denum != r1. denum * r2. num;
}

inline bool operator < ( const rational& r1, const rational& r2 )
{
   return r1. num * r2. denum < r1. denum * r2. num;
}

inline bool operator > ( const rational& r1, const rational& r2 )
{
   return r1. num * r2. denum > r1. denum * r2. num;
}

inline bool operator <= ( const rational& r1, const rational& r2 )
{
   return r1. num * r2. denum <= r1. denum * r2. num;
}

inline bool operator >= ( const rational& r1, const rational& r2 )
{
   return r1. num * r2. denum >= r1. denum * r2. num;
}

std::ostream& operator << ( std::ostream& stream, const rational& r );


#endif


