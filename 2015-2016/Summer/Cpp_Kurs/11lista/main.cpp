#include "figures.h"
#include <vector>
std::ostream& operator << (std::ostream& stream, const surface& s)
{
	s.getsurf().print(stream);
	return stream;
}

std::ostream& operator << ( std::ostream& stream,
                            const std::vector< surface > & table )
{
    for( size_t i = 0; i < table. size( ); ++ i )
    {
        stream << i << "-th element = " << table [i] << "\n";
    }
    return stream;
}
void print_statistics( const std::vector< surface > & table )
{
    double total_area = 0.0;
    double total_circumference = 0.0;
    for( const auto& s : table )
    {
        std::cout << "adding info about " << s << "\n";
        total_area += s. getsurf( ). area( );
        total_circumference += s. getsurf( ). circumference( );
    }
    std::cout << "total area is " << total_area << "\n";
    std::cout << "total circumference is " << total_circumference << "\n";
}

int main()
{
//ZAPYTAC
//DLACZEGO surface s1(circle()); DAJE ROZNE GLUPOTY?????
//ZAPYTAC
//ZAPYTAC
//ZAPYTAC
	surface s1{circle()};
	surface s2(circle(2,2,2));
	std::cout << s1 <<"\n";
	s1 = s2;
	std::cout << s2 << "\n";
	s1 = s1;
	std::cout << s1 << "\n";
	surface s3 = surface(circle(4,2,1) ); 
	
	

#if 0
	rectangle r(0,0,1,1);
	r.print(std::cout);
	std::cout << r.circumference() << "\n";
	rectangle* tab[2] = {r.clone(), new rectangle(1,1,1,1)};
	for(size_t i=0; i< 2 ; i++)
	{
		tab[i]->print(std::cout);
	}
	delete tab[0];
	delete tab[1];


	triangle t(0,0,0,1,1,1);
	t.print( std::cout );
	std :: cout << t.area() << "\n";
	
	surface sur( std::move(rectangle()) );
#endif	
	return 0;
}
