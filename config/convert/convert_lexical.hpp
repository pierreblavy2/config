//============================================================================
// Author  : Pierre BLAVY 2018
// Version : 1.0
// License : GPL 3.0 or any later version :
//           https://www.gnu.org/licenses/gpl-3.0-standalone.html
//============================================================================

//This program (config) is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>


#ifndef LIB_CONVERT_LEXICAL_HPP_
#define LIB_CONVERT_LEXICAL_HPP_

#include <convert/convert.hpp>
#include <string>
#include <boost/lexical_cast.hpp>

namespace config{
  struct Config_tag;
}

template<typename Numeric_t>
struct Convert_t<
  Numeric_t,
  std::string, //From_t
  typename std::enable_if<
        std::is_integral      <Numeric_t>::value
	  | std::is_floating_point<Numeric_t>::value
  , config::Config_tag>::type
>{
	typedef Numeric_t   To_t;
	typedef std::string From_t;

	static To_t run(const From_t &f){
		return boost::lexical_cast<Numeric_t>(f);
	}
};


#endif /* LIB_CONVERT_LEXICAL_HPP_ */
