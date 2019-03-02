
#ifndef TREE_INCLUDED
#define TREE_INCLUDED  1


#include <iostream>
#include <vector>
#include <string>


class tree;

// struct trnode should be invisible to the user of tree. This can be 
// obtained by making it a private number of tree. 
// In this exercise, we leave it like this, because it is simpler.
// In real code, trnode should be defined inside tree.


struct trnode 
{
   std::string f;
   std::vector< tree > subtrees;
   
   size_t refcnt;
      // The reference counter: Counts how often this trnode is referred to.

   trnode( const std::string& f, const std::vector< tree > & subtrees, 
           size_t refcnt )
      : f{f},
        subtrees{ subtrees },
        refcnt{ refcnt }
   { }

   trnode( const std::string& f, std::vector< tree > && subtrees,
           size_t refcnt )
      : f{f},
        subtrees{ std::move( subtrees )}, 
        refcnt{ refcnt }
   { }


};


class tree
{
   trnode* pntr;

public: 
   tree( const std::string& f ) 
      :  pntr( new trnode( f, { }, 1 ))
   { }

   tree( const std::string& f, const std::vector< tree > & subtrees )   
      : pntr( new trnode( f, subtrees, 1 ))
   { } 
 
   tree( const std::string& f, std::vector< tree > && subtrees )
      : pntr( new trnode( f, std::move( subtrees ), 1 ))
   { }


   tree( const tree& t )
   	:pntr{t.pntr}
   	{
   		(pntr->refcnt)++;
   	}
      // There is no need to write tree( tree&& t ),
      // because we cannot improve. 

   void operator = ( tree&& t ){
   	std::swap(pntr,t.pntr);
   } 
   void operator = ( const tree& t ){
   	*this=tree(t);
   }
 
   const std::string& functor( ) const{	return pntr->f;   }
# if 0   
   std::string& functor( ){
   	ensure_not_shared();
   	return pntr->f;
   }
#endif
   const tree& operator [ ] ( size_t i ) const{	
   	return pntr->subtrees[i];
   }
#if 0
   tree& operator [ ] ( size_t i ){
   	ensure_not_shared();
   	return pntr->subtrees[i];
   }
#endif
   size_t nrsubtrees( ) const{	return pntr->subtrees.size();	} 

   ~tree( ){
   	if(--pntr->refcnt==0){
   		delete pntr;
   	}
   }
   
   size_t getaddress( ) const
	{
	return reinterpret_cast< size_t > ( pntr );
	}


private: 
public: 
   // Delete public, when the thing is tested:

   void ensure_not_shared( ){
   	if(pntr->refcnt!=1){
   		pntr->refcnt--;
   		pntr = new trnode(pntr->f, pntr->subtrees, 1);
   	}
   }
   
   void replace_subtree(size_t i, const tree &newtree );
   void replace_functor(const std::string& functor);

};

std::ostream& operator << ( std::ostream& stream, const tree& t );
   // Doesn't need to be friend, because it uses only functor( ),
   // nrsubtrees( ) and [ ].
tree subst( const tree &t, const std::string &var, const tree &val);
bool operator == (const tree& t1,const tree& t2);
bool operator != (const tree& t1,const tree& t2);
#endif

