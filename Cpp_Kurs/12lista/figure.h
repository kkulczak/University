

#ifndef FIGURE_INCLUDED
#define FIGURE_INCLUDED  1

#include <initializer_list>
#include <iostream> 
#include <string>
#include <vector>

struct figure
{

   std::vector< std::string > repr; 
   
   figure( std::initializer_list< const char* > ); 

};

std::ostream& operator << ( std::ostream& , const figure& f );

figure glider( );
figure square( ); 
figure toad( ); 
figure glider_gun( );
figure glider_eater( );
figure glider_eater2( );
figure blinker( );
figure pulsar( );
figure pentadecathlon( );
figure relay( ); 


#endif


