
#include "rational.h"
#include "matrix.h"


int main(  )
{	
	
   rational r1( 2, 6 );
   rational r2( 4, 3 ); 
   rational r3( 5,6 );
   rational r4( 1, 2 );
   matrix m=matrix::identity();
   matrix m4=matrix::identity();
	vector v(r1,r2);
   matrix m1 = { { 2, 3 }, { 4, 6 } };


   matrix m2 = { { 5,4 }, { 6, rational(1,2) } }; 


   matrix m3 = { { 4,5}, { -1, 2 }};
	
   std::cout << (m1*m2)*m3 - m1*(m2*m3) << "\n";
	std::cout << m1*m2+m1*m3 - m1*(m2+m3) << "\n";
   std::cout << (m1+m2)*m3 - (m1*m3+m2*m3) << "\n";
   std::cout << m1*(m2*v) - (m1*m2)*v << "\n";
   	m4=m1*m2;
   std::cout << "\n" << m1.determinant()*m2.determinant() - (m4).determinant() << "\n\n";
  	std::cout << m2*m2.inverse() - m<< "\n";	
  	std::cout << m2.inverse()*m2 - m << "\n";

   
   
   rational x11(1,2);
   rational x12(1,3);
   rational x21(-2,7);
   rational x22(2,8);
   rational y11(-1,3);
   rational y12(2,7);
   rational y21(2,5);
   rational y22(-1,7);
   
   matrix x= { {x11, x12 } , { x21, x22} };
   matrix y= { {y11, y12 } , {y21, y22 } };
   	
   m=x*y;
   std::cout << m << std::endl;
   std::cout << x.inverse();
   
	return 0;
}

