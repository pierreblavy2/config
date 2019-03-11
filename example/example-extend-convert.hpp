//============================================================================
// Author  : Pierre BLAVY 2018
// Version : 1.0
// License : GPL 3.0 or any later version :
//           https://www.gnu.org/licenses/gpl-3.0-standalone.html
//============================================================================

//This program (convert) is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>

//--- Add custom conversions ---
//Custom conversion are used in config by
// - Value::to<My_type>(),
// - Value_v::get_unique<My_type>(...)
// - Value_v::load_unique<My_type>(...)
// - Value_v::get_multiple< Container<My_type> >(...)
// - Value_v::load_multiple< Container<My_type> >(...)
//
//To make all this functions works, you need to extend the Convert_t class
//to convert to My_type from std::string, in the config::Config_tag context

#include <convert.hpp>
#include <string>
namespace config{struct Config_tag;}

enum class My_type{cat,dog,unknown};

struct Convert_t<
My_type,           //To_t
  std::string,       //From_r
  config::Config_tag //Context_t
>{
	typedef My_type To_t;
	typedef std::string From_t;

	static To_t run(const From_t &f){
		if(f=="cat"){return My_type::cat;}
		if(f=="dog"){return My_type::dog;}
		return My_type::unknown;
	}
};
