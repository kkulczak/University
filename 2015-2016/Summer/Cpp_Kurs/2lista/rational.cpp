
#include "rational.h"
#include <stdexcept>
// Complete these methods:

#if 1 

int rational::gcd( int n1, int n2 ){
	if(n1<n2){
		int temp=n1;
		n1= n2;
		n2= temp;
	}
	if(n2==0)	return n1;
	return gcd(n2, n1 % n2);
}

void rational::normalize(){
	if(num==0)	{denum=1; return;}
	if(denum==0)	{
		throw std::runtime_error( "Mianownik==0");
		return;
	}
	if(denum<0){
		denum*=-1;
		num*=-1;
	}
	int temp=gcd(num<0?-num:num, denum);
	num/=temp;
	denum/=temp;
}

rational operator - ( rational r ){
	return r*(-1);
}

rational operator + ( const rational& r1, const rational& r2 ){
	return rational( r1.getnum() * r2.getdenum() + r2.getnum() * r1.getdenum(), r1.getdenum() * r2.getdenum());
}

rational operator - ( const rational& r1, const rational& r2 ){
	return rational( r1.getnum() * r2.getdenum() - r2.getnum() * r1.getdenum(), r1.getdenum() * r2.getdenum());
}

rational operator * ( const rational& r1, const rational& r2 ){
	return rational( r1.getnum() * r2.getnum() , r1.getdenum() * r2.getdenum() );
}

rational operator / ( const rational& r1, const rational& r2 ){
	return rational( r1.getnum() * r2.getdenum(), r1.getdenum() * r2.getnum() );
}

bool operator == ( const rational& r1, const rational& r2 ){
	return (r1.getnum() == r2.getnum() && r1.getdenum() == r2.getdenum());
}
bool operator != ( const rational& r1, const rational& r2 ){
	return !(r1 == r2);
}

std::ostream& operator << ( std::ostream& stream, const rational& r ){
	stream << r.getnum() << " / " << r.getdenum();
	return stream;
} 

#endif

