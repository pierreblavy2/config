//============================================================================
// Author  : Pierre BLAVY 2018
// Version : 1.0
// License : GPL 3.0 or any later version :
//           https://www.gnu.org/licenses/gpl-3.0-standalone.html
//============================================================================

//This program (convert) is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>

#ifndef LIB_CONVERT_STRING_CSTRING_HPP_
#define LIB_CONVERT_STRING_CSTRING_HPP_

#include "convert.hpp"
#include <string>

namespace config{
  struct Config_tag;
}


template<>
struct Convert_t<std::string, const char *,Config_tag>{
	static constexpr bool is_implemented=true;
	typedef std::string   To_t;
	typedef const char * From_t;

	static To_t run(const From_t &f){
		return std::string(f);
	}
};

template<>
struct Convert_t<const char *,std::string ,Config_tag>{
	static constexpr bool is_implemented=true;

	typedef const char * To_t;
	typedef std::string  From_t;

	static To_t run(const From_t &f){
		return f.c_str();
	}
};

#endif /* LIB_CONVERT_STRING_CSTRING_HPP_ */
