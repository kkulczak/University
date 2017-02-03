#ifndef _STACK
#define _STACK 1
#include <iostream>
#include <initializer_list>
#include <stdexcept>
class stack
{
	size_t current_size;
	size_t current_capacity;
		// size_t is an integer number >= 0. It should be used for
		// sizes of objects, for indexing (because an index lies
		// between 0 and the size of the object) and for hash values
		// (because a hash value will be used for indexing.)
		// size_t is guaranteed to be big enough for the memory
		// of every computer, now and in the future.
		// size_t is an alias. Hence you need to include something
		// from standard library in order to have it.
	double* tab;
		// class invariant is that tab is always
		// allocated with a block with current_capacity.
		// We ignore the fact that normally,
		// elements between current_size and current_capacity
		// are not initialized.
	void ensure_capacity( size_t c );
		// Ensure that stack has capacity of at least c.
public:
	stack( )
		: current_size{0},
		  current_capacity{0},
		  tab{NULL}
	{}  
		                 // Constructs empty stack.
	stack( std::initializer_list< double > d )
		: current_size{d.size()},
		  current_capacity{d.size()},
		  tab{new double[d.size()]}
	{	

		;
		size_t j=0;
		for(auto i=d.begin(); i != d.end(); i++){
			tab[j] = * i;
			j++;
		}
	}
		// So that you can write s = { 1,2,3 };
			// You need d. size( ) and for( double d : s ) .....
	stack( const stack& s ) 
		: current_size{s.current_size},
		  current_capacity{s.current_capacity},
		  tab{new double[s.current_capacity] }
	{
		
		for(size_t i= 0; i < s.size(); i++){
			tab[i]= s.tab[i];
		}
	}
	
	~stack( ){
		delete[] tab;
	}
	void operator = ( const stack& s );
		// These are the essential methods.
		// Later we will also encounter
		// void operator = ( stack&& s ) and
		// stack( stack&& s ).
	void push( double d ){
		ensure_capacity( current_size + 1 );
		tab[ current_size++ ] = d;
	}
	  // Use ensure_capacity, so that
		// pushing is always possible, as
		// long as memory is not full.
	void pop( ){
		
			current_size--;
		
	}
		// Remove one element from the stack. It’s OK to write
		// code that crashes, as long as you write clearly what are
		// your preconditions, so:
		// PRECONDITION:  The stack is not empty.
	void reset( size_t s ){
		while( current_size != s ){
			pop();
		}
	}
		// Pops element until stack has size s.
		// PRECONDITION: s <= current_size.
	double& top( ){
		return tab[current_size-1];
	}
	double top( ) const{
		return tab[current_size-1];
	}
		// The second one is used when stack was declared const.
		// The first one allows assignment.
		// Both have precondition that the stack is non-empty.
	size_t size( ) const { return current_size; }
	bool empty( ) const { return current_size == 0; }
	
	friend std::ostream& operator << (std::ostream& stream, const stack &s);
	double operator [] (size_t i) const{
		if(i >= current_size){
		throw std::runtime_error("Wrong Iterator\n");
		}
	 	return tab[ current_size - 1 - i];
	 }
	double& operator [] (size_t i){
		if(i >= current_size){
		throw std::runtime_error("Wrong Iterator\n");
		}
		return tab[ current_size - 1 - i];
	}
	void operator += ( double d){
		push(d);
	}
	void operator += (const stack& s){
		size_t temp= s.current_size;
		for( size_t i=0; i < temp; i++){
			push(s.tab[i]);
		}
	}
	

};
inline stack operator + (const stack& s1, const stack& s2){
		stack res{s1};
		res += s2;
		return res;
}

#endif
