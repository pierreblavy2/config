//============================================================================
// Author  : Pierre BLAVY 2018
// Version : 1.0
// License : GPL 3.0 or any later version :
//           https://www.gnu.org/licenses/gpl-3.0-standalone.html
//============================================================================

//This program (container) is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>


//--- Add custom containers ---
//Custom container are used in config by
// - Value_v::get_multiple< Container<My_type> >(...)
// - Value_v::load_multiple< Container<My_type> >(...)
//
//To make custom containers work you need to provide
// - cont::Value_type_t,
//   There is a default implementation that define type as Container::value_type
// - cont::Add_back_t or cont::Add_anywhere_t
//   If you do provide Add_back_t, values will be added in the same order as
//   the one from the configuration file.
//
//Conversions from std::string to values in the containers type
//(i.e. from std::string to cont::Value_type_t<My_container>::type)
//are handled automaticallty trough the convert interface, so you don't have
//to do them while extending a container in cont::Xxx_t


//Example with a dummy custom container.
struct My_container{
	double one;
	double two;
	double three;
	size_t which_one = 0;
};


#include <container/container.hpp>
#include <stdexcept>

struct cont::Value_type_t<My_container>{
	  typedef double type;
};

template<>
struct cont::Add_back_t<My_container>{
	Add_back_t()=delete;
	typedef My_container container_t;

	template<typename Value_t>
	static void run(container_t &c, Value_t &&v){
		if(c.which_one==0){c.one   = v; ++c.which_one; return; }
		if(c.which_one==1){c.two   = v; ++c.which_one; return; }
		if(c.which_one==2){c.three = v; ++c.which_one; return; }
        throw std::out_of_range();
	}

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::constant;
};

//not required, as Add_back_t exists :
template<>
struct cont::Add_anywhere_t<My_container>{
	Add_anywhere_t()=delete;
	typedef My_container container_t;

	template<typename Value_t>
	static void run(container_t &c, Value_t &&v){
		//
		cont::Add_back_t<My_container>::run(c,v);
	}

    static constexpr bool is_implemented = true;
    static constexpr Complexity complexity = Complexity::constant;
};


