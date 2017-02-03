#include "tree.h"

std::ostream& operator << ( std::ostream& stream, const tree& t ){
	stream << t.functor() /*<< "(" << t.getaddress() << ")"*/ <<"\n";
	for( size_t i=0; i < t.nrsubtrees(); i++){	stream << t[i];	}
	return stream;
}

tree subst( const tree &t, const std::string &var, const tree &val ){
	if(t.nrsubtrees()==0){
		if(t.functor() == var)	return val;
		else	return t;
	}
		tree res(t);
		for(size_t i=0; i< res.nrsubtrees(); i++){
				res.replace_subtree(i, subst( res[i] , var, val) );
		}
		return res;
}

void tree::replace_subtree(size_t i, const tree &newtree ){
	if(newtree.pntr != pntr->subtrees[i].pntr){
	ensure_not_shared();
	pntr->subtrees[i] = newtree;
	}
}

void tree::replace_functor(const std::string& functor){
	if(functor != pntr->f){
	ensure_not_shared();
	pntr->f = functor;
	}
}

bool operator == (const tree& t1,const tree& t2) {
	std::vector<std::pair<tree, tree>> pairs { {t1,t2} };
	while(pairs.size()){
		std::pair<tree, tree> last = pairs.back();
		pairs.pop_back();
  		if ( last.first.functor() != last.second.functor()) {
   		return false;
   	}
   	else if (last.first.nrsubtrees() != last.second.nrsubtrees()) {
			return false;
		}
		else{
			for(size_t i=0; i<last.first.nrsubtrees(); i++){
				pairs.push_back({last.first[i],last.second[i]});
			}
		}
  }
  return true;
}

bool operator != (const tree& t1,const tree& t2) {
	return !(t1 == t2);
}
