
// Written by Hans de Nivelle, June 2011.

#include "bigint.h"


bigint::bigint( unsigned int x )
   : sign( 1 ) 
{
   word w1 = x & 0XFFFF;
   word w2 = ( x & 0XFFFF0000 ) >> 16;

   if( w2 )
   {
      repr. push_back( w1 );
      repr. push_back( w2 );
   }
   else
   {
      if( w1 )
         repr. push_back( w1 );
   }

}

bigint::bigint( int x )
{
   unsigned int y;
   if( x < 0 )
   {
      sign = -1;
      y = - x;
   }
   else
   {
      sign = 1;
      y = x;
   }

   while( y )
   {
      repr. push_back( y & 0XFFFF );
      y >>= 16;
   }
} 

void bigint::add( std::vector< word > :: iterator p1,
                  std::vector< word > :: const_iterator q1,
                  std::vector< word > :: const_iterator q2,
                  word factor )
{
   unsigned int carry = 0;

   std::vector< word > :: iterator p = p1;
   std::vector< word > :: const_iterator q = q1;

   while( q != q2 )
   {
      carry += *p + *q * factor;
      *p = carry & 0XFFFF;

      carry >>= 16;
      
      ++ p; ++ q;
   }

   while( carry )
   {
      carry += *p;
      *p = carry & 0XFFFF;

      carry >>= 16;

      ++ p; 
   }
}


bigint::word bigint::subtract( std::vector< word > :: iterator p1,
                               word restword, 
                               std::vector< word > :: const_iterator q1,
                               std::vector< word > :: const_iterator q2,
                               word factor )
{
   std::vector< word > :: iterator p = p1;
   std::vector< word > :: const_iterator q = q1;

   unsigned int carry = 0;
      // Carry is zero or negative. In case there is something in carry,
      // the most significant part must be FFFF.

   while( q != q2 )
   {
      carry += *p;
      carry -= factor * *q;

      *p = carry & 0XFFFF;

      carry >>= 16;

      // We need sign extension in carry, because it represents a 
      // negative number. 

      if( carry )
         carry |= 0XFFFF0000;

      ++ p; ++ q;
   }

   carry += restword;  
   restword = carry & 0XFFFF; 

   carry >>= 16; 

   // If we have something left in carry, we decrease factor,
   // and add *q1 ... *q2 to *p1 ... *p2, until we are positive again. 

   if( carry )
   {
      // We are now negative, so we need to go another time through
      // zero to become positive again.

      carry = 0;
      while( carry == 0 )
      {
         p = p1;
         q = q1; 
         while( q != q2 )
         {
            carry += *p + *q;
            *p = carry & 0XFFFF;

            carry >>= 16;

            ++ p;
            ++ q;
         }

         carry += restword; 
         restword = carry & 0XFFFF;

         carry >>= 16;

         -- factor; 
      }
   }

   if( restword )
      throw std::runtime_error( "restword should have been zero" );

   return factor;
}


void bigint::add( std::vector< word > :: const_iterator p1,
                  std::vector< word > :: const_iterator p2,
                  std::vector< word > :: const_iterator q1,
                  std::vector< word > :: const_iterator q2,
                  std::vector< word > :: iterator r1,
                  std::vector< word > :: iterator r2 )
{
   unsigned int carry = 0;

   std::vector< word > :: const_iterator p = p1;
   std::vector< word > :: const_iterator q = q1;
   std::vector< word > :: iterator r = r1;

   while( p != p2 && q != q2 )
   {
      carry += *p + *q;
      *r = carry & 0XFFFF;

      carry >>= 16;

      ++ p; ++ q; ++ r; 
   }

   // The following is correct because either p != p2 or
   // q != q2. This guarantees that at most one of the while loops
   // will be entered. 

   while( p != p2 )
   {
      carry += *p;
      *r = carry;

      carry >>= 16;

      ++ p; ++ r; 
   }

   while( q != q2 )
   {
      carry += *q;
      *r = carry;

      carry >>= 16;

      ++ q; ++ r;
   }

   while( r != r2 )
   {   
      *r = carry; 
      carry >>= 16;
      ++ r;

   }

   if( carry )
      throw std::runtime_error( "there is carry left" ); 
}


void bigint::subtract( std::vector< word > :: const_iterator p1,
                       std::vector< word > :: const_iterator p2,
                       std::vector< word > :: const_iterator q1,
                       std::vector< word > :: const_iterator q2,
                       std::vector< word > :: iterator r1,
                       std::vector< word > :: iterator r2 )
{
   std::vector< word > :: const_iterator p = p1;
   std::vector< word > :: const_iterator q = q1;
   std::vector< word > :: iterator r = r1;

   unsigned int carry = 0;
   while( p != p2 && q != q2 )
   {
      carry += *p;
      carry -= *q;

      *r = carry & 0XFFFF;

      carry >>= 16;

      // We need sign extension in carry, because it represents a
      // negative number.

      if( carry )
         carry |= 0XFFFF0000;

      ++ p; ++ q; ++ r;
   }

   // The following code is correct because either
   // p == p2 or q == q2. This implies that only one of
   // the while loops will be entered.

   while( p != p2 )
   {
      carry += *p;
      *r = carry; 

      carry >>= 16;
      
      if( carry )
         carry |= 0XFFFF0000;

      ++ p; ++ r;
   }

   while( q != q2 )
   {
      carry -= *q;
      *r = carry;

      carry >>= 16;


      if( carry )
         carry |= 0XFFFF0000;

      ++ q; ++ r;
   }

   while( r != r2 )
   {
      *r = carry;
      carry >>= 16;

      if( carry )
         carry |= 0XFFFF0000;
  
      ++ r;
   }

   if( carry )
      throw std::runtime_error( "there is carry left" );
}


void bigint::addorsub( const bigint& b1, 
                       const bigint& b2, int s2, bigint& r )
{
   if( b1. sign == s2 * b2. sign )
   {
      r. ensure( b1. repr. size( ) + 1 );
      r. ensure( b2. repr. size( ) + 1 ); 

      r. sign = b1. sign; 

      add( b1. repr. begin( ), b1. repr. end( ),
           b2. repr. begin( ), b2. repr. end( ),
           r. repr. begin( ), r. repr. end( )); 
   }
   else
   {
      if( compare( b1. repr, b2. repr ) == -1 )
      {
         // We have b1 + -b2 and b1 < b2. 

         r. sign = s2 * b2. sign; 

         r. ensure( b2. repr. size( )); 
         subtract( b2. repr. begin( ), b2. repr. end( ),
                   b1. repr. begin( ), b1. repr. end( ),
                   r. repr. begin( ), r. repr. end( ));
      }
      else
      {
         r. sign = b1. sign; 

         r. ensure( b1. repr. size( ));
         subtract( b1. repr. begin( ), b1. repr. end( ),
                   b2. repr. begin( ), b2. repr. end( ),
                   r. repr. begin( ), r. repr. end( )); 
      }
   }  
   r. reduce( );
}


void bigint::multiply( const std::vector< word > & v1,
                       const std::vector< word > & v2,
                       std::vector< word > & res )
{
   std::vector< word > :: iterator q = res. begin( );
 
   for( std::vector< word > :: const_iterator
           p = v1. begin( );
           p != v1. end( );
           ++ p )
   {
      add( q, v2. begin( ), v2. end( ), *p );
      ++ q;
   }
}


// These are helper functions, belonging to the different types 
// of division estimators.

namespace
{

   inline void shift( bigint::word& x1, bigint::word& x2, bigint::word& x3, 
                      bigint::word m, unsigned int k )
   {
      x3 >>= k;
      x3 |= ( x2 & m ) << ( 16 - k );

      x2 >>= k;
      x2 |= ( x1 & m ) << ( 16 - k );

      x1 >>= k;
   }


   inline void shift( bigint::word& y1, bigint::word& y2, bigint::word m, 
                      unsigned int k )
   {
      y2 >>= k;
      y2 |= ( y1 & m ) << ( 16 - k );

      y1 >>= k;
   }


   inline bool lesseq( bigint::word v1, bigint::word v2, bigint::word v3, 
                       bigint::word w1, bigint::word w2, bigint::word w3 )
   {
      if( v1 < w1 ) return true;
      if( v1 > w1 ) return false;

      if( v2 < w2 ) return true;
      if( v2 > w2 ) return false;

      if( v3 <= w3 ) return true;
      return false;
   }


   inline void shiftleft( bigint::word& w1, 
                          bigint::word& w2, 
                          bigint::word& w3 )
   {
      w1 <<= 1;
      if( w2 & 0X8000 )
         w1 |= 1;

      w2 <<= 1;
      if( w3 & 0X8000 )
         w2 |= 1;

      w3 <<= 1;
   }


   inline void shiftright( bigint::word& w1, 
                           bigint::word& w2, 
                           bigint::word& w3 )
   {
      w3 >>= 1;
      if( w2 & 1 )
         w3 |= 0X8000;

      w2 >>= 1;
      if( w1 & 1 )
         w2 |= 0X8000;

      w1 >>= 1;
   }


   inline void subtract( bigint::word& w1, bigint::word& w2, bigint::word& w3,
                         bigint::word v1, bigint::word v2, bigint::word v3 )
   {
      unsigned int carry = w3;
      carry -= v3;
      w3 = carry;
 
      carry >>= 16;
      if( carry & 0XFFFF )
         carry |= 0XFFFF0000;
 
      carry += w2;
      carry -= v2;
      w2 = carry;

      carry >>= 16;
      if( carry & 0XFFFF )
         carry |= 0XFFFF0000;

      carry += w1;
      carry -= v1;
      w1 = carry;
   }
}


#if 0 
 
unsigned int bigint::divide( word x1, word x2, word x3,
                             word y2, word y3 )
{
   word y1 = 0;

   unsigned int result = 0;
   unsigned int bit = 1;

   while( lesseq( y1, y2, y3, x1, x2, x3 ) && ( y1 & 0X8000 ) == 0 )
   {
      bit <<= 1;
      shiftleft( y1, y2, y3 );
   }

   while( bit != 0 )
   {
      // printf( "bit = %x\n", bit ); 
      // printf( "X = %x %x %x\n", x1, x2, x3 );
      // printf( "Y = %x %x %x\n", y1, y2, y3 );

      if( lesseq( y1, y2, y3, x1, x2, x3 ))
      {
         subtract( x1, x2, x3, y1, y2, y3 );
         result |= bit;
      }

      shiftright( y1, y2, y3 );
      bit >>= 1;
   }

   
   return result;
}

#endif



#if 1

// This function can off by 2. 

unsigned int bigint::divide( word x1, word x2, word x3, 
                             word y1, word y2 )
{
#if 0 
   std::cout << "divide : ";
   std::cout << "[ " << x1 << ", " << x2 << ", " << x3 << " ] / ";
   std::cout << "[ " << y1 << ", " << y2 << " ]\n";
#endif 
   if( x1 == 0 )
      return (( static_cast< unsigned int > ( x2 ) << 16 ) |
                static_cast< unsigned int > ( x3 )) /
             (( static_cast< unsigned int > ( y1 ) << 16 ) |
                static_cast< unsigned int > ( y2 ));

  
   if( x1 & 0X8000 )
   {
      x3 = x2;
      x2 = x1;
      x1 = 0;

      y2 = y1;
      y1 = 0;
   }
     
   if( x1 & 0X7F80 )
   {
      shift( x1, x2, x3, 0X00FF, 8 );
      shift( y1, y2, 0X00FF, 8 );
   }

   if( x1 & 0X0078 )
   {
      shift( x1, x2, x3, 0X000F, 4 );
      shift( y1, y2, 0X000F, 4 );
   }

   if( x1 & 0X0006 )
   {
      shift( x1, x2, x3, 0X0003, 2 );
      shift( y1, y2, 0X0003, 2 );
   }

   if( x1 )
   {
      shift( x1, x2, x3, 0X0001, 1 );
      shift( y1, y2, 0X0001, 1 );
   }

#if 0 
   std::cout << "reduced to "; 
   std::cout << "[ " << x1 << ", " << x2 << ", " << x3 << " ] / ";
   std::cout << "[ " << y1 << ", " << y2 << " ]\n";
#endif 

   unsigned int est = (( static_cast< unsigned int > ( x2 ) << 16 ) | 
                         static_cast< unsigned int > ( x3 )) / 
                      (( static_cast< unsigned int > ( y1 ) << 16 ) | 
                         static_cast< unsigned int > ( y2 ));

   return est; 
}

#endif 
   
   
std::vector< bigint::word > 
bigint::divide( const std::vector< word > & d, std::vector< word > & rest )
{
   
   if( d. size( ) == 0 || d. back( ) == 0 )
      throw std::runtime_error( "cannot divide by zero" );

   if( d. size( ) <= rest. size( ))
   {
      std::vector< word > quotient = 
         std::vector< word > ( rest. size( ) - d. size( ) + 1 ); 

      // fd will the front digit of d. We use fd to estimate how
      // many times the division will fit. 
      // fd must be viewed as two words, with the first word before
      // the comma, and the second word behind the comma. 

      word d1 = d. back( ); 
      word d2 = 0;
      if( d. size( ) > 1 )
         d2 = d. end( ) [ -2 ];

      std::vector< word > :: iterator q1 = rest. end( ) - d. size( ); 
         // Possible with vector< > :: iterators.
      std::vector< word > :: iterator q2 = rest. end( ); 

      std::vector< word > :: iterator dig = quotient. end( );
      while( dig != quotient. begin( ))      
      {
         -- dig; 

         // We need to make an estimation of how many times we can
         // subtract d from rest.
       
         word x1 = 0;
         if( q2 != rest. end( ))
            x1 = *q2; 
         word x2 = q2 [ -1 ];
         word x3 = 0;
         if( d. size( ) > 1 )
            x3 = q2 [ -2 ];
        
         unsigned int factor = divide_fp( x1, x2, x3, d1, d2 ); 

         // The estimated factor can be one too high, but we know that
         // the true factor necessarily fits in a single digit:

         if( factor >= 65536 ) 
            factor = 65535;
 
         *dig = subtract( q1, x1, d. begin( ), d. end( ), factor );
        
         if( q2 != rest. end( ))
            *q2 = 0; 
 
         if( *dig != factor && *dig + 1 != factor )
            throw std::runtime_error( "something went wrong" ); 

         -- q1;
         -- q2; 
      }
      return quotient;
   }
   else
      return std::vector< word > ( ); 
}


int bigint::compare( std::vector< word > :: const_iterator p1,
                     std::vector< word > :: const_iterator p2,
                     unsigned int len )
{
   while( len )
   {
      -- p1;
      -- p2;
      -- len;

      if( *p1 != *p2 )
      {
         if( *p1 < *p2 ) 
            return -1;
         else
            return 1;
      }
   }
   return 0;
}


int bigint::compare( const std::vector< word > & v1, 
                     const std::vector< word > & v2 )
{
   // This works only for normalized numbers of course:

   if( v1. size( ) != v2. size( ))
   {
      if( v1. size( ) < v2. size( ))
         return -1;
      else
         return 1;
   }

   unsigned int k = v1. size( );

   return compare( v1. end( ), v2. end( ), k );
}


int bigint::compare( const bigint& i1, const bigint& i2 )
{
   // We do this, because 0 can have both positive and negative sign.

   int s1 = i1. sign;
   if( i1. repr. size( ) == 0 ) 
      s1 = 0;

   int s2 = i2. sign;
   if( i2. repr. size( ) == 0 )
      s2 = 0;

   if( s1 < s2 ) return -1;
   if( s1 > s2 ) return 1;

   if( s1 == 0 ) return 0;
   if( s1 < 0 )
      return compare( i2. repr, i1. repr );
   else
      return compare( i1. repr, i2. repr );
}

   
bool bigint::testmachine( )
{
   // We check that words have 16 bits:

   word w = 1;
   for( unsigned int i = 0; i < 16; ++ i )
   {
      if( w == 0 ) return 0;
      if( w < 0 ) return 0;
      w <<= 1;
   }
   if( w != 0 ) return 0; 

   // We don't want sign extension in right shifts:

   w = 0X8000;
   w >>= 1;
   if( w != 0X4000 )
      return false;

   unsigned int x = 1;
   for( unsigned int i = 0; i < 32; ++ i )
   {
      if( x == 0 ) return 0;
      if( x < 0 ) return 0; 
      x <<= 1;
   }
   if( x != 0 ) return 0;

   return true; 
}



unsigned int bigint::checksum( unsigned int prime ) const
{
   unsigned int sum = 0;
   unsigned int factor = 1;

   for( std::vector< word > :: const_iterator
           p = repr. begin( );
           p != repr. end( );
           ++ p )
   {
      sum = sum + factor * *p;
      sum = sum % prime;

      factor <<= 16; 
      factor = factor % prime;
   }

   if( sign < 0 )
   {
      sum = prime - sum;
      if( sum == prime )
         sum = 0;
   } 
   return sum;
}


bigint bigint::gcd( bigint i1, bigint i2 )
{

   while( i1. repr. size( ) && i2. repr. size( ))
   {
      if( compare( i1. repr, i2. repr ) == -1 )
      {
         divide( i1. repr, i2. repr );
         i2. reduce ( );
      }
      else
      {
         divide( i2. repr, i1. repr );
         i1. reduce( );
      }
   }

   if( i1. repr. size( ) == 0 ) 
      return i2;
   return i1;
}


double bigint::approximation( ) const
{
   double res = 0.0;
   double weight = 1.0;
   for( std::vector< word > :: const_iterator
           p = repr. begin( );
           p != repr. end( );
           ++ p )
   {
      res += weight * *p;
      weight *= 65536.0;
   }

   if( sign == 1 )
      return res;
   else
      return -res;
}


bigint bigint::factorial( unsigned int k )
{
   if( k == 0 )
      return 1;
   else
      return factorial( k - 1 ) * k;
}


std::ostream& operator << ( std::ostream& stream, bigint b )
{
   if( b. sign < 0 )
   {
      b = -b; 
      stream << '-';
   }

   std::string res;
   while( b != 0 )
   {
      unsigned int c = ( b % 10 ). getunsigned( );
      res. push_back( c + '0' );
      b /= 10;
   }
 
   if( res. size( ))
   {
      unsigned int i = res. size( );
      while( i != 0 )
      {
         -- i;
         stream << res[i];
      }
   }
   else
      stream << '0';

   return stream;
 
   for( std::vector< bigint::word > :: const_iterator
           p = b. repr. begin( );
           p != b. repr. end( );
           ++ p )
   {
      stream << *p << "  ";
   }
   return stream;
}



