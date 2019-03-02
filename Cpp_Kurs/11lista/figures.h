#ifndef FIGURES_INCLUDED
#define FIGURES_INCLUDED
#include <iostream>

struct surf
{
    virtual double area( ) const = 0;
    virtual double circumference( ) const = 0;
    virtual surf* clone( ) const & = 0;
    virtual surf* clone( ) && = 0;
    virtual void print( std::ostream& ) const = 0;
    virtual ~surf( ) = default;
};

struct rectangle : public surf
{
    double x1;
    double y1;
    double x2;
    double y2;
    
    rectangle(const rectangle & r)
    :	x1{r.x1},
    	y1{r.y1},
    	x2{r.x2},
    	y2{r.y2}
    {}
    
    rectangle(double nx1,double ny1,double nx2,double ny2)
    :	x1{nx1},
    	y1{ny1},
    	x2{nx2},
    	y2{ny2}
    {}
    
    rectangle()
    : rectangle(0,0,1,1)
    {}
    
    ~rectangle()
    {}
     
    double area( ) const override;
    double circumference( ) const override;
    rectangle* clone( ) const & override;
    rectangle* clone( ) && override;
    void print( std::ostream& ) const override;
};

struct triangle : public surf
{	
    double x1, y1; // Positions of corners.
    double x2, y2;
    double x3, y3;
    
    triangle(const triangle & r)
    :	x1{r.x1},
    	y1{r.y1},
    	x2{r.x2},
    	y2{r.y2},
    	x3{r.x3},
    	y3{r.y3}
    {}
    
    triangle(triangle && r)
    :	x1{std::move(r.x1)},
    	y1{std::move(r.y1)},
    	x2{std::move(r.x2)},
    	y2{std::move(r.y2)},
    	x3{std::move(r.x3)},
    	y3{std::move(r.y3)}
    {}
    
    triangle(double nx1,double ny1,double nx2,double ny2, 
    							double nx3, double ny3)
    :	x1{nx1},
    	y1{ny1},
    	x2{nx2},
    	y2{ny2},
    	x3{nx3},
    	y3{ny3}
    {}
    
    triangle()
    : triangle(0,0,0,1,1,1)
    {}
    
    ~triangle()
    {}
    
    double area( ) const override;
    double circumference( ) const override;
    triangle* clone( ) const & override;
    triangle* clone( ) && override;
    void print( std::ostream& ) const override;
};
struct circle : public surf
{
    double x; // Position of center.
    double y;
    double radius;
    
    circle(circle const & c)
    :	x{c.x},
    	y{c.y},
    	radius{c.radius}
    {}
    
    circle(circle && c)
    :	x{std::move(c.x)},
    	y{std::move(c.y)},
    	radius{std::move(c.radius)}
    {}     	
    
    circle(double nx, double ny, double nradius)
    :	x{nx},
    	y{ny},
    	radius{nradius}
    {}
    
    circle()
    : circle(0,0,1)
    {}
    
    ~circle()
    {}
    	
    double area( ) const override;
    double circumference( ) const override;
    circle* clone( ) const & override;
    circle* clone( ) && override;
    void print( std::ostream& ) const override;
};

struct surface
{
	surf* ref;
	
	surface( const surface& s)
	: ref{s.ref->clone()}
	{}
	
	surface( surface&& s)
	:	ref{std::move(s.ref)->clone()}
	{}
	
	surface( const surf& s)
	:	ref{s.clone()}
	
	{}
	
	surface( surf&& s)
	:	ref{std::move(s).clone()}
	{}
	
		~surface()
	{
		delete ref;
	}
	
	void operator = (const surface& s);
	void operator = (surface&& s);
	void operator = (const surf& s);
	void operator = ( surf&& s);
	const surf& getsurf() const {return *ref;}
};

#endif
