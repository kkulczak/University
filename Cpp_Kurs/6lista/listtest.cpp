
#include "listtest.h"

#include <random>
#include <chrono>
#include <algorithm>
#if 1
void listtest::sort_assign( std::list< std::string > & v ){
	for(auto j=v.begin(); j != v.end(); j++){
		for(auto i=v.begin(); i!=j; i++){
			if( *i > *j ){
				std::string s= *i;
				*i = *j;
				*j = s;
			}
		}
	}
}

void listtest::sort_move( std::list< std::string > & v ){
	//v.sort();
	for(auto j=v.begin(); j != v.end(); j++){
		for(auto i=v.begin(); i!=j; i++){
			if( *i > *j ){
				std::swap(*i, *j);
			}
		}
	}
}
#endif
std::ostream& operator << (std::ostream& out, const std::list<std::string> &l){
	for(const std::string& i : l)	out << i << ", ";
	out << '\n';
	return out;
}

std::list<std::string> listtest::vector_to_list(const std::vector<std::string> &v){
   	std::list<std::string> l;
   	for(auto i : v){
   		l.push_back(i);
   	}
   	return l;
   }



