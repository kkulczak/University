#include "figures.h"
#include <cmath>
#define PI 3.14159265359

//	rectangle

double rectangle::area() const
{
	return abs( x2 - x1 ) * abs( y1 - y2 );
}

double rectangle::circumference() const
{
	return 2.0 * ( abs( x2 - x1 ) + abs( y1 - y2 ) );
}

rectangle* rectangle::clone () const &
{	
	return new rectangle(*this);
}

rectangle* rectangle::clone( ) && 
{
	return new rectangle(*this);
}

void rectangle::print( std::ostream & stream) const
{
	stream << "Rectangle: ( " << x1 << " , " << y1 << " ) , ( " << x2 ;
	stream << " , " << y2 << " )\n";  
}

//	triangle

double triangle::area() const
{	
	return abs( (x1-x2)*(y3-y2) - (y1-y2)*(x3-x2) ) / 2.0  ;
}

double triangle::circumference() const
{
	return 	sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) ) +
		   	sqrt( (x2-x3)*(x2-x3) + (y2-y3)*(y2-y3) ) +
				sqrt( (x3-x1)*(x3-x1) + (y3-y1)*(y3-y1) );
}

triangle* triangle::clone () const &
{
	return new triangle(*this);
}

triangle* triangle::clone( ) && 
{
	return new triangle(std::move(*this));
}

void triangle::print( std::ostream & stream) const
{
	stream << "Triangle: ( " << x1 << " , " << y1 << " ) , ( " << x2 ;
	stream << " , " << y2 << " ) , ( " ;
	stream << x3 << " , " << y3 << " )\n";  
}

// circle

double circle::area() const
{	
	return PI * radius * radius  ;
}

double circle::circumference() const
{
	return 	2.0 * PI * radius;
}

circle* circle::clone () const &
{
	return new circle(*this);
}

circle* circle::clone( ) && 
{
	return new circle(std::move(*this));
}

void circle::print( std::ostream & stream) const
{
	stream << "circle: ( " << x << " , " << y << " ) r: " << radius;
	stream << '\n';
}

// surface
void surface::operator = (const surface& s)
{	
	surf* temp = s.ref->clone();
	delete ref;
	ref = temp;	
}

void surface::operator = (surface&& s)
{
	std::swap(ref, s.ref);
}

void surface::operator = (const surf& s)
{	
	surf* temp = s.clone();
	delete ref;
	ref = temp;
}

void surface::operator = (surf && s)
{	
	surf* temp = std::move(s).clone();
	delete ref;
	ref = temp;
}







