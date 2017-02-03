#include "fifteen.h"

std::ostream& operator << ( std::ostream& stream, const fifteen& f ){
	for(size_t i=0; i < f.dimension; i++)	stream << "--";
	for(size_t i=0; i < f.dimension; i++ ){
		stream << "\n";
		for(size_t j=0; j < f.dimension; j++){
			stream << f.table[i][j] << " "; 
		}
	}
	stream << "\n";
	for(size_t i=0; i < f.dimension; i++)	stream << "--";	
	stream << "\n";
	return stream;
}



