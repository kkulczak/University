#include "stack.h"


int main(){
	stack s1 = { 1, 2, 3, 4, 5 };
	std::cout << s1 << "\n";
	
	stack s2 = s1; // Copy constructor.
	std::cout << s2 << "\n";
	
	// j is not size_t, because multiplying size_t with itself is
	// unnatural:
	for( unsigned int j = 0; j < 20; ++ j )
	s2. push( j * j );
	std::cout << s2 << "\n";
	
	s1 = s2;
	std::cout << s1 << "\n";
	
	// Assignment.
	s1 = s1;
	std::cout << s1 << "\n";
	
	// Always check for self assignment.
	s1 = { 100,101,102,103 };
	std::cout << s1 << "\n";
	
	// Works because the compiler inserts constructor and
	// calls assignment with the result.
#if 1
	// Won’t compile. In order to get it compiled, remove const:
	stack& s = s1;
	s. top( ) = 20;
	s. push(15);
	std::cout << s << "\n";
	#endif
	
	s1+=s1;
	std::cout<< s1 << "\n";
	
	return 0;
}
