#ifndef LIB_CONVERT_CONVERT_BOOL_HPP_
#define LIB_CONVERT_CONVERT_BOOL_HPP_



#include <convert/convert.hpp>

#include <algorithm>
#include <string>
#include <stdexcept>


namespace config{
  struct Config_tag;
}


template<>
struct Convert_t<bool,std::string,config::Config_tag>{
	typedef bool        To_t;
	typedef std::string From_t;

	static To_t run(const From_t &s){
		std::string f=s;
		std::transform(f.begin(), f.end(), f.begin(), ::tolower);

		if(f=="y"){return true;}
		if(f=="n"){return false;}

		if(f=="yes"){return true;}
		if(f=="no") {return false;}

		throw(std::runtime_error("Cannot convert string to bool, string="+s));
	}
};



#endif /* LIB_CONVERT_CONVERT_BOOL_HPP_ */
