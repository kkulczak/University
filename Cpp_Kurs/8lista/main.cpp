#include <vector>
#include <map>
#include <iostream>
#include <unordered_map>

struct case_insensitive{
	bool operator ()(const std::string& s1, const std::string& s2) const{
		auto p1 = s1.begin();
		for(auto p2 = s2.begin(); p2 != s2.end(); p2++){
			if(p1 == s1.end())	return false;
			char c1 = tolower(*p1);
			char c2 = tolower(*p2);
			if (c1 == c2) {p1++;continue;}
			return ( c1 < c2 );
		}
		if(p1 != s1.end())	return true;
		return false;	
	}
};

std::map<std::string,unsigned int,case_insensitive> frequencytable(const std::vector<std::string> & text){
	std::map<std::string,unsigned int,case_insensitive> map;
	for( const auto &i : text){
		map[i]++;
	}
	return map;
}

std::ostream& operator << (std::ostream& stream, const std::map< std::string, unsigned int,case_insensitive> & freq){
	stream << "Frequency words table:\n";
	for(const auto &i: freq){
		stream << i.first << "\t" << i.second <<"\n";
	}
	stream << "\n";
	return stream;
}

struct case_insensitive_hash{
	size_t operator ()(const std::string& s) const{
		size_t hash = 0;
		for(const auto& i: s){
			hash = (hash * 131) + tolower(i);
		}
		return hash;
	}
};
struct case_insensitive_equality{
	bool operator () (const std::string& s1, const std::string& s2 ) const{
		if (s1.size() != s2.size()) return false;
		for(auto p1 = s1.begin(), p2 = s2.begin(); p1 != s1.end(); p1++, p2++){
		  if (tolower(*p1) != tolower(*p2)) return false;
		}
		return true;
	}
};

template<typename Map> Map frequencytable_impl(const std::vector<std::string> & text){
	Map map;
	for(const auto & i:text)	map[i]++;
	return map;
}


std::unordered_map< std::string, unsigned int, case_insensitive_hash, case_insensitive_equality> hashed_frequencytable(const std::vector<std::string> & text){
	return frequencytable_impl<std::unordered_map< std::string, unsigned int, case_insensitive_hash, case_insensitive_equality>>(text);
}


/*
std::unordered_map< std::string, unsigned int, case_insensitive_hash, case_insensitive_equality> hashed_frequencytable(const std::vector<std::string> & text){
	std::unordered_map< std::string, unsigned int, case_insensitive_hash, case_insensitive_equality> map;
	for(const auto & i:text)	map[i]++;
	return map;
}
*/
std::ostream& operator << (std::ostream& stream,const std::unordered_map<std::string, unsigned int, case_insensitive_hash , case_insensitive_equality> &  freq ) {
	stream << "Frequency words table:\n";
	for(const auto &i: freq){
		stream << i.first << "\t" << i.second <<"\n";
	}
	stream << "\n";
	return stream;
}


int main(){
	std::cout << "\n" << frequencytable({"AA","aA","Aa","this","THIS",});
	case_insensitive_hash h;
	std::cout << h("xxx") << " " << h("XXX") << "\n";
	std::cout << h("AbC") << " " << h("aBC") << "\n";
	case_insensitive_equality e;
	std::cout << e("xxx","XXX") << "\n";
	std::cout << "\n" << hashed_frequencytable({"AA","aA","Aa","this","THIS",});
	return 0;
}

























