#include "stack.h"

void stack::ensure_capacity( size_t c ){
	if( current_capacity < c ){
											// New capacity will be the greater of c and
											// 2 * current_capacity.
		if( c < 2 * current_capacity )	c = 2 * current_capacity;
	double* newtab = new double[ c ];
	for( size_t i = 0; i < current_size; ++ i )	newtab[i] = tab[i];
	current_capacity = c;
	delete[] tab;
	tab = newtab;
	}
}

void stack::operator = ( const stack& s ){
		if( &s != this){
			current_size= s.current_size;
			current_capacity= s.current_capacity;
			delete[] tab;
			tab = new double[s.current_size];
			for(size_t i=0; i < s.current_size; i++) tab[i] = s.tab[i];
		}
	}

std::ostream& operator << (std::ostream& stream, const stack& s){
	for(size_t i=0; i<s.current_size; i++){
		stream << s.tab[i] << "\t";
	}		
	stream << "\n";
	return stream;
}






	
