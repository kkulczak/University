
#include "matching.h"
#include <string>
#if 1
std::list< matching > match( tree from, tree into ){
    std::cout << "matching " << from << " into " << into << "\n";

   matching m;

   std::vector< std::pair< tree, tree >> stack  = { { from, into } };

   while( stack. size( )){
   	//Cout
   	for( auto t : stack )	std::cout << "[  " << t. first << " = " << t. second << "  ]    ";	
      std::cout << "\n";
      
      std::pair<tree,tree > current = {stack.back()};
      stack. pop_back( );
      
      
      if( m.isvariable( current.first.functor()) && current.first.nrsubtrees() == 0 ){
      	if( m.isdefined( current.first.functor())  ){
      		if( ! (m.subst.at(current.first.functor()) == current.second)){
      			return {};
      		}
      		else{continue;}
      	}
      	else{
      		m.assign(current.first.functor(),current.second);
      	}
      }
      else if( current.first.functor() == current.second.functor() && current.first.nrsubtrees() == current.second.nrsubtrees() ){
      	for(size_t i=0; i<current.first.nrsubtrees(); i++){
      		stack.push_back({current.first[i],current.second[i]});
      	}
      }
      else	return {};
   }
   return {m};


   // Success: return { m };
   // Failure: return { };

}
 #endif
tree matching::operator ( )(const tree& t) const{
	if(isvariable(t.functor()) && t.nrsubtrees() == 0){
		if(isdefined(t.functor())){
			return subst.at(t.functor());
		}
		else{
			tree ret(t);
			return ret;
		}
	}
	else{
		tree ret(t);
		for(size_t i=0; i<t.nrsubtrees(); i++){
			ret.replace_subtree(i,  (*this)(t[i]) );
		}
		return ret;
	}
}

std::ostream& operator << ( std::ostream& out, const matching& m )
{
   out << "matching: ";
   for( const auto& p : m. subst )  
   {
      out << p. first << " := " << p. second << "\n";
   }
   return out;
}


