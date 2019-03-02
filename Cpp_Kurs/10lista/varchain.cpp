
#include "varchain.h"
#include <algorithm>


std::ostream& operator << ( std::ostream& out, const powvar & p )
{
   if( p.n == 0 )
   {
      out << "1"; // Should not happen, but we still have to print something.
      return out;
   }

   out << p.v;
   if( p.n == 1 )
      return out;

   if( p.n > 0 )
      out << "^" << p.n;
   else
      out << "^{" << p.n << "}";
   return out;
}


std::ostream& operator << ( std::ostream& out, const varchain& c )
{
   if( c. isunit( ))
   {
      out << "1";
      return out;
   }

   for( auto p = c. repr. begin( ); p != c. repr. end( ); ++ p )
   {
      if( p != c. repr. begin( ))
         out << ".";
      out << *p;
   }

   return out;
}


int varchain::power( ) const 
{
   int p = 0;
   for( auto pv : repr )
      p += pv. n;
   return p;
}

//	Task 1
bool cmp_powvar(powvar a, const powvar b){
 return (a.v < b.v);
}

void varchain::normalize(){
	std::sort(repr.begin(), repr.end(), cmp_powvar);
	std::vector< powvar > norm_repr;
	for( auto i = repr.begin(); i!= repr.end(); i++){
		int n= i->n;
		while( i+1 != repr.end() && (i+1)->v == i->v ){
			n += (++i)->n;
		}
		if ( n ){
			norm_repr.emplace_back(i->v, n);
		}
		
	}
	repr = std::move( norm_repr );
}
//	Task2

int varchain::compare( const varchain& c1, const varchain& c2 ){
	auto i = c1.repr.begin();
	for(auto j = c2.repr.begin(); j!=c2.repr.end(); j++){
		if(i == c1.repr.end() )	return -1;
		if(i->v == j->v){
			if(i->n != j->n )	{
   			return (i->n - j->n );
	   	}
		}
		else{
			if(i->v < j->v)	return -1;
			return 1;
		}
		i++;
	}
	if(i == c1.repr.end() )	return 0;
	return 1;
}

//	Task3
varchain operator * ( varchain c1, const varchain& c2 ){
	c1.repr.reserve( c1.repr.size() + c2.repr.size() );
	for(const auto & i : c2.repr)	c1.repr.push_back(i);
	c1.normalize();
	return c1;
}























