
#ifndef VECTOR_INCLUDED
#define VECTOR_INCLUDED 1

// There is nothing in this class. One could make operators
// +,-,*,/, but I was too lazy to do that.
// Feel free to add them if you wish.

struct vector
{
   rational x;
   rational y;

   vector( const rational& x, const rational& y )
      : x{x}, y{y}
   { }

};

inline std::ostream& operator << ( std::ostream& out, const vector& v )
{
   out << "( " << v. x << ", " << v. y << " )"; 
   return out;
}

inline vector operator - (const vector& v1, const vector& v2){
	return vector( v1.x - v2.x, v1.y - v2.y );
}

#endif

