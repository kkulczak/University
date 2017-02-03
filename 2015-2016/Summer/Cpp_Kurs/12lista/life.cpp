
// The main file as written by Szymon Koper, June 2013.
// Revised by Hans de Nivelle, June 2014.

#include <iostream>
#include <vector>
#include <random>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "grid.h"
#include "figure.h" 
#include <chrono>
#include <thread>

#include <GL/gl.h>

#define USEGRAPHICS     0

int main( )
{
//sf::Window App(sf::VideoMode(640, 480, 32), "SFML Window"); 
//sf::RenderWindow App(sf::VideoMode(640, 480, 32), "SFML Window");
#define TEST 1
#if TEST
grid a(40,40);
a.addfigure(0,39, glider_gun( ));
std::cout << a;
for(int i=0; i<2; i++)
{
	a.nextgeneration();
	std::cout << a;
}
#endif

return 0;
#if 1
#if USEGRAPHICS
   unsigned int gridsizex = 500;
   unsigned int gridsizey = 500;

   std::chrono::duration< unsigned int, std::milli > delay{ 1000 };

#else
   unsigned int gridsizex = 32;
   unsigned int gridsizey = 32;
#endif

   grid g( gridsizex, gridsizey );

   try
   {
      g. addfigure( 10, 10, glider_gun( ));  
      g. addfigure( 40, 10, relay( )); 
   }
   catch( const grid::wrongchar& w )
   {
      std::cout << w << "\n";
   }

#if USEGRAPHICS
   {
      unsigned int windowsizex = 2 * gridsizex;
      unsigned int windowsizey = 2 * gridsizey;

      while( windowsizex < 500 )
      {
         windowsizex += windowsizex / 2;
         windowsizey += windowsizey / 2;
      }

      // Note that all SFML used in this program, is SFML 1.6.
      // The differences are small, but irritating.

      sf::Window window( 
           sf::VideoMode( windowsizex, windowsizey ), "Game of Life" );

      glClearColor( 0.05, 0.05, 0.05, 1.0 );
      glClearDepth( 1.0 );
      glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
      glMatrixMode( GL_PROJECTION );
      glLoadIdentity( );
      glScalef( 1.0 / ( gridsizex / 2 ), 1.0 / ( gridsizey / 2 ), 1.0 );

      glColor3f( 0.6, 0.7, 1 );

      bool running = true;
      while( running ) 
      {
         sf::Event event;
         while( window.GetEvent(event) )
         {
            if (event.Type == sf::Event::Closed)
               running = false;
            else if (event.Type == sf::Event::Resized)
               glViewport(0, 0, event.Size.Width, event.Size.Height );
         }

         glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
         g.plot();
         window.Display();
         std::this_thread::sleep_for( delay );

         g. nextgeneration( ); 
      }
      std::cout << "bye bye\n";
      return 0; 
   }
#else
   {
      char c = ' ';
      do 
      {
         std::cout << g << '\n';
         g. nextgeneration();
         std::cout << "press key to continue, q to quit\n";
         c = getchar( ); 
      }
      while( c != 'q' && c != 'Q' ); 
      return 0;
   }
#endif 
#endif
}
