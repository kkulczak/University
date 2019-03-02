
#include "rational.h"


std::ostream& operator << ( std::ostream& stream, const rational& r )
{ 
   if( r. denum != 1 )
      stream << "( " << r. num << " / " << r. denum << " )";
   else
      stream << r. num; 

   return stream;
}


