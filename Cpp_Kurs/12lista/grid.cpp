#include "grid.h"



grid::grid( const grid& g )
:	xsize{g.xsize},
	ysize{g.ysize},
	c( new cell[g.xsize * g.ysize])
{
	for(unsigned int i=0; i < xsize * ysize; i++)
	{
		c[i].s0 = g.c[i].s0;
		c[i].s1 = g.c[i].s1;
	}
}

grid::grid( grid&& g)
:	xsize{g.xsize},
	ysize{g.ysize},
	c{g.c}
{
	g.c = nullptr;
}

void grid::operator = ( const grid& g )
{
	*this = grid(g);
}

void grid::operator = ( grid&& g )
{
	std::swap(xsize, g.xsize);
	std::swap(ysize, g.ysize);
	std::swap(c, g.c);
}

grid::~grid( )
{
	delete [] c;
}

void grid::clear()
{
	for(unsigned int i=0; i < xsize * ysize; i++)
	{
		c[i].s0=false;
		c[i].s1=false;
	}
}

void grid::addfigure( unsigned int x, unsigned int y,
				std::initializer_list< const char* > p )
{	
	int tempy=0;
	for(auto i = p.begin(); i != p.end(); i++)
	{
		for(unsigned int j=0; (*i)[j] !=  '\0'; j++ )
		{
			c[place_in_table(x+j,y-tempy)].s0 = isonchar( (*i)[j] );
		}
		tempy++;
	}	
}

void grid::addfigure( unsigned int x, unsigned int y, const figure& f )
{	
	int tempy=0;
	for(const auto & i : f.repr)
	{
		int tempx = 0;
		for(const auto & j : i )
		{
			c[place_in_table(x+tempx,y-tempy)].s0 = isonchar(j);
			tempx++;
		}
		tempy++;
	}	
}

void grid::nextgeneration()
{
	for(unsigned int i=0; i < xsize; i++)
	{
		for(unsigned int j=0; j < ysize; j++)
		{
			int temp=0;
			if(is_allowed(i-1,j-1))	temp += c[place_in_table(i-1,j-1)].s0;
			if(is_allowed(i-1,j))	temp += c[place_in_table(i-1,j)].s0;
			if(is_allowed(i-1,j+1))	temp += c[place_in_table(i-1,j+1)].s0;
			if(is_allowed(i,j-1))	temp += c[place_in_table(i,j-1)].s0;
			if(is_allowed(i,j+1))	temp += c[place_in_table(i,j+1)].s0;
			if(is_allowed(i+1,j-1))	temp += c[place_in_table(i+1,j-1)].s0;
			if(is_allowed(i+1,j))	temp += c[place_in_table(i+1,j)].s0;
			if(is_allowed(i+1,j+1))	temp += c[place_in_table(i+1,j+1)].s0;
			if(temp == 3)
			{
				c[place_in_table(i,j)].s1 = true;
				continue;
			}
			if(temp == 2 && c[place_in_table(i,j)].s0 )
			{
				c[place_in_table(i,j)].s1 = true;
				continue;
			}
			c[place_in_table(i,j)].s1 = false;
		}
	}
	for(unsigned int i=0; i < xsize * ysize; i++)
	{
		std::swap(c[i].s0,c[i].s1);
	}
	
}

std::ostream& operator << ( std::ostream& stream, const grid& g)
{
	stream << "\n";
	for(int y= g.ysize-1 ; y >= 0 ; y--)
	{
		for(unsigned int x=0; x <= g.xsize-1; x++)
		{
			if( g.c[ g.place_in_table(x,y) ].s0 )	stream << "X";
			else stream << ".";
		}
		stream << "\n";
	}
	stream << "\n";
	return stream;
}










